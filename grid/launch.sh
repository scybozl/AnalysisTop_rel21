
for i in {1..345}; do
  cp mppui_batch-mt174p0.sbx submit/mppui_batch-mt174p0-$i.sbx &&
  sed -i "s|STARTSEED=1|STARTSEED=$i|g" submit/mppui_batch-mt174p0-$i.sbx &&
  sbatch submit/mppui_batch-mt174p0-$i.sbx;
done

