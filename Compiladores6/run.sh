rm back_end.in
echo "Front end:"
./front_end < script.set

time ./a.out < back_end.in
