$cert_dir = "../../certs/"

openssl genrsa -out $cert_dir/key.pem
openssl req -new -key $cert_dir/key.pem -out $cert_dir/csr.pem
openssl x509 -req -days 1 -in $cert_dir/csr.pem -signkey $cert_dir/key.pem  -out $cert_dir/cert.pem
rm $cert_dir/csr.pem

echo ""
echo "Deleting csr.pem"
echo "All done"