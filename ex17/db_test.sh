set -e
echo "Testing ex17 DB"

./ex17 murok.db s 100 Shirou semiya@eiyuu.jp 
./ex17 murok.db g 100 Shirou semiya@eiyuu.jp
./ex17 murok.db d 100 
