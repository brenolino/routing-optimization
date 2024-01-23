cd ..

date > Resultados/saidaA-n48-k7.txt
echo "====================================================================" >> Resultados/saidaA-n48-k7.txt
echo "                R E S U L T A D O S    G U L O S O                  " >> Resultados/saidaA-n48-k7.txt
echo "====================================================================" >> Resultados/saidaA-n48-k7.txt

for x in $(seq 1 1 1); 
do
  { time ./execGrupo6 A-n48-k7 0 0 1; } 2>&1 | grep real >> Resultados/saidaA-n48-k7.txt
done

echo "====================================================================" >> Resultados/saidaA-n48-k7.txt
echo "     R E S U L T A D O S    G U L O S O    R A N D O M I Z A D O    " >> Resultados/saidaA-n48-k7.txt
echo "====================================================================" >> Resultados/saidaA-n48-k7.txt

for x in `seq 1 1 10`;
do
  { time ./execGrupo6 A-n48-k7 1 0.05 1000; } 2>&1 | grep real >> Resultados/saidaA-n48-k7.txt
done;

echo "====================================================================" >> Resultados/saidaA-n48-k7.txt
echo "     R E S U L T A D O S    G U L O S O    R A N D O M I Z A D O    " >> Resultados/saidaA-n48-k7.txt
echo "====================================================================" >> Resultados/saidaA-n48-k7.txt

for x in `seq 1 1 10`;
do
  { time ./execGrupo6 A-n48-k7 1 0.1 1000; } 2>&1 | grep real >> Resultados/saidaA-n48-k7.txt
done;

echo "====================================================================" >> Resultados/saidaA-n48-k7.txt
echo "     R E S U L T A D O S    G U L O S O    R A N D O M I Z A D O    " >> Resultados/saidaA-n48-k7.txt
echo "====================================================================" >> Resultados/saidaA-n48-k7.txt

for x in `seq 1 1 10`;
do
  { time ./execGrupo6 A-n48-k7 1 0.15 1000; } 2>&1 | grep real >> Resultados/saidaA-n48-k7.txt
done;

echo "====================================================================" >> Resultados/saidaA-n48-k7.txt
echo "     R E S U L T A D O S    G U L O S O    R A N D O M I Z A D O    " >> Resultados/saidaA-n48-k7.txt
echo "====================================================================" >> Resultados/saidaA-n48-k7.txt

for x in `seq 1 1 10`;
do
  { time ./execGrupo6 A-n48-k7 1 0.3 1000; } 2>&1 | grep real >> Resultados/saidaA-n48-k7.txt
done;

echo "====================================================================" >> Resultados/saidaA-n48-k7.txt
echo "     R E S U L T A D O S    G U L O S O    R A N D O M I Z A D O    " >> Resultados/saidaA-n48-k7.txt
echo "====================================================================" >> Resultados/saidaA-n48-k7.txt

for x in `seq 1 1 10`;
do
  { time ./execGrupo6 A-n48-k7 1 0.5 1000; } 2>&1 | grep real >> Resultados/saidaA-n48-k7.txt
done;

echo "============================================================================" >> Resultados/saidaA-n48-k7.txt
echo "R E S U L T A D O S    G U L O S O    R A N D O M I Z A D O    R E A T I V O" >> Resultados/saidaA-n48-k7.txt
echo "============================================================================" >> Resultados/saidaA-n48-k7.txt

for x in `seq 1 1 10`;
do
  { time ./execGrupo6 A-n48-k7 2 1 3000; } 2>&1 | grep real >> Resultados/saidaA-n48-k7.txt
done;