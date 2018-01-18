EXE="./lsv_revSyn"
rm size.log
rm ctrl.log
for i in {0..40319};
do
   specfile=$i.spec
   $EXE -spec allcase/$specfile -output $i.tfc 1>1.out
#   rm $i.tfc
   echo $i
done
