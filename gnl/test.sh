#!/usr/bin/env sh
set -eu

# ----- Ayarlar -----
CC=${CC:-gcc}
W="-Wall -Wextra -Werror"
ASANFLAGS=${ASANFLAGS:-}
# Örn: ASANFLAGS="-fsanitize=address -g" ekleyebilirsin

BS_LIST="1 2 3 7 42 1024 4096 65536"
HUGE_BS="1000000000" # bilerek stack taşır (aşağıda ayrı test)

FIXDIR="./gnl_fixtures"
mkdir -p "$FIXDIR"

# ----- Fixture üretimi -----
# 1) boş dosya
: > "$FIXDIR/empty.txt"

# 2) sadece newline
printf "\n" > "$FIXDIR/only_nl.txt"

# 3) tek satır, newline yok
printf "hello" > "$FIXDIR/one_no_nl.txt"

# 4) tek satır, newline var
printf "hello\n" > "$FIXDIR/one_with_nl.txt"

# 5) bir sürü kısa satır
#    (1..1000) hepsi newline ile biter
seq 1 1000 > "$FIXDIR/many_short_lines.txt"

# 6) son satırı newline'sız
seq 1 999 > "$FIXDIR/last_no_nl.txt"
printf "1000" >> "$FIXDIR/last_no_nl.txt"

# 7) buffer'dan uzun tek satır (+\n)
#    10000 'A' + '\n'
yes A | tr -d '\n' | head -c 10000 | sed 's/$/\n/' > "$FIXDIR/long_line_with_nl.txt"

# 8) devasa tek satır, newline yok (5MB)
head -c 5242880 /dev/zero | tr '\0' 'B' > "$FIXDIR/huge_no_nl.txt"

# 9) CRLF içeren dosya (Windows satır sonları)
printf "line1\r\nline2\r\nlast" > "$FIXDIR/crlf.txt"

# 10) UTF-8 (çok baytlı) karakterlerle satırlar
printf "şığçöÜ\n🐉 ejderha\n最后一行" > "$FIXDIR/unicode.txt"

# 11) directory fd (okuma hatası beklenir; sadece crash olmasın)
DIR_PATH="."
# 12) invalid fd testini program içinde tetiklemek yerine negatif fd ile çağırmayacağız.

# ----- Yardımcı: derle & çalıştır & karşılaştır -----
build_and_run () {
  BS="$1"
  echo "==> Build BUFFER_SIZE=$BS"
  $CC $W $ASANFLAGS -D BUFFER_SIZE="$BS" tests/gnl_cat.c get_next_line.c get_next_line_utils.c -o gnl_cat_"$BS"

  # Her fixture için cat karşılaştırması
  FAIL=0
  for f in empty.txt only_nl.txt one_no_nl.txt one_with_nl.txt \
           many_short_lines.txt last_no_nl.txt long_line_with_nl.txt \
           huge_no_nl.txt crlf.txt unicode.txt
  do
    printf "   [%s] " "$f"
    if diff -u --label "gnl" --label "cat" <(./gnl_cat_"$BS" "$FIXDIR/$f") <(cat "$FIXDIR/$f") >/dev/null 2>&1; then
      echo "PASS"
    else
      echo "FAIL"
      FAIL=1
    fi
  done

  # Çoklu fd testi (sadece crash etmesin)
  echo "   [multi-fd]"
  $CC $W $ASANFLAGS -D BUFFER_SIZE="$BS" tests/gnl_multi.c get_next_line.c get_next_line_utils.c -o gnl_multi_"$BS"
  if ./gnl_multi_"$BS" "$FIXDIR/many_short_lines.txt" "$FIXDIR/last_no_nl.txt" "$FIXDIR/unicode.txt" >/dev/null; then
    echo "   multi-fd: PASS"
  else
    echo "   multi-fd: FAIL"
    FAIL=1
  fi

  # Directory okunamaz; beklenen davranış: NULL döndürmek (çökmeden)
  echo "   [directory-fd]"
  if ./gnl_cat_"$BS" "$DIR_PATH" >/dev/null 2>&1; then
    echo "   directory-fd: WARN (okundu?)"
  else
    echo "   directory-fd: PASS (çökme yok, hata beklenirdi)"
  fi

  return $FAIL
}

# ----- Normal boyutlu BS testleri -----
OVERALL=0
for BS in $BS_LIST; do
  if build_and_run "$BS"; then
    :
  else
    OVERALL=1
  fi
done

# ----- Aşırı büyük BUFFER_SIZE testi (beklenen: STACK OVERFLOW / segfault) -----
echo "==> EXTRA: BUFFER_SIZE=$HUGE_BS (beklenen: stack overflow/segfault)"
if $CC $W $ASANFLAGS -D BUFFER_SIZE="$HUGE_BS" tests/gnl_cat.c get_next_line.c get_next_line_utils.c -o gnl_cat_huge 2>/dev/null; then
  if ./gnl_cat_huge "$FIXDIR/only_nl.txt" >/dev/null 2>&1; then
    echo "   beklenmedik şekilde çalıştı (ortam stack limiti çok yüksek olabilir)."
  else
    echo "   EXPECTED FAIL: büyük BUFFER_SIZE ile stack overflow/segfault"
  fi
else
  echo "   derleme başarısız (muhtemel integer overflow uyarıları)."
fi

exit $OVERALL
