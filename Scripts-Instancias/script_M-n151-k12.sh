cd ..

date > Resultados/saidaM-n151-k12.txt
echo "====================================================================" >> Resultados/saidaM-n151-k12.txt
echo "                R E S U L T A D O S    G U L O S O                  " >> Resultados/saidaM-n151-k12.txt
echo "====================================================================" >> Resultados/saidaM-n151-k12.txt

for x in $(seq 1 1 1); 
do
  { time ./execGrupo6 M-n151-k12 0 0 1; } 2>&1 | grep real >> Resultados/saidaM-n151-k12.txt
done

echo "====================================================================" >> Resultados/saidaM-n151-k12.txt
echo "     R E S U L T A D O S    G U L O S O    R A N D O M I Z A D O    " >> Resultados/saidaM-n151-k12.txt
echo "====================================================================" >> Resultados/saidaM-n151-k12.txt

for x in `seq 1 1 10`;
do
  { time ./execGrupo6 M-n151-k12 1 0.05 1000; } 2>&1 | grep real >> Resultados/saidaM-n151-k12.txt
done;

echo "====================================================================" >> Resultados/saidaM-n151-k12.txt
echo "     R E S U L T A D O S    G U L O S O    R A N D O M I Z A D O    " >> Resultados/saidaM-n151-k12.txt
echo "====================================================================" >> Resultados/saidaM-n151-k12.txt

for x in `seq 1 1 10`;
do
  { time ./execGrupo6 M-n151-k12 1 0.1 1000; } 2>&1 | grep real >> Resultados/saidaM-n151-k12.txt
done;

echo "====================================================================" >> Resultados/saidaM-n151-k12.txt
echo "     R E S U L T A D O S    G U L O S O    R A N D O M I Z A D O    " >> Resultados/saidaM-n151-k12.txt
echo "====================================================================" >> Resultados/saidaM-n151-k12.txt

for x in `seq 1 1 10`;
do
  { time ./execGrupo6 M-n151-k12 1 0.15 1000; } 2>&1 | grep real >> Resultados/saidaM-n151-k12.txt
done;

echo "====================================================================" >> Resultados/saidaM-n151-k12.txt
echo "     R E S U L T A D O S    G U L O S O    R A N D O M I Z A D O    " >> Resultados/saidaM-n151-k12.txt
echo "====================================================================" >> Resultados/saidaM-n151-k12.txt

for x in `seq 1 1 10`;
do
  { time ./execGrupo6 M-n151-k12 1 0.3 1000; } 2>&1 | grep real >> Resultados/saidaM-n151-k12.txt
done;

echo "====================================================================" >> Resultados/saidaM-n151-k12.txt
echo "     R E S U L T A D O S    G U L O S O    R A N D O M I Z A D O    " >> Resultados/saidaM-n151-k12.txt
echo "====================================================================" >> Resultados/saidaM-n151-k12.txt

for x in `seq 1 1 10`;
do
  { time ./execGrupo6 M-n151-k12 1 0.5 1000; } 2>&1 | grep real >> Resultados/saidaM-n151-k12.txt
done;

echo "============================================================================" >> Resultados/saidaM-n151-k12.txt
echo "R E S U L T A D O S    G U L O S O    R A N D O M I Z A D O    R E A T I V O" >> Resultados/saidaM-n151-k12.txt
echo "============================================================================" >> Resultados/saidaM-n151-k12.txt

for x in `seq 1 1 10`;
do
  { time ./execGrupo6 M-n151-k12 2 1 3000; } 2>&1 | grep real >> Resultados/saidaM-n151-k12.txt
done;