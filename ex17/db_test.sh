set -e
echo "Testing ex17 DB"

echo "Deleting user if it exists"
./ex17 murok.db d 99 
echo "Setting new user"
./ex17 murok.db s 99 Shirou semiya@eiyuu.jp 
echo "Getting new user"
./ex17 murok.db g 99 

