tensorhex.exe --geom meshd.srf --bgmesh meshd.srf --initsurfacebgm ^
  --generatecurvescaffolds ^
  --insertbc 2.2 0.8 -2.3 1.51 0.390626953132324 0 0 625 0 1.5625 1 0 ^
  --insertbc -1.8 0.8 2.3 1.51 0.9765625 0 0.5859375 625 0 0.9765625 1 0 ^
  --savefield onlyBC.nt3m ^
  --savebgmesh meshd_edit.srf ^
  --updateweighttables --enablepseudotensors ^
  --gensurfacefieldwithbcs ^
  --disablepseudotensors ^
  --savefield tensor.nt3m ^
  --savetfdFLANN tensor.tfd 40 40 40 1. ^
  --persevere

volmesh --BUB --PBUB -infile meshd.srf -overlapcorrection -0.1 -tfd tensor.tfd  ^
  -remeshqualitymode -out meshanid.srf -e 3000 -f 25000

tensorhex.exe --geom meshd_edit.srf --bgmesh meshd_edit.srf ^
  --initsurfacebgm --loadfield tensor.nt3m ^
  --resamplefieldontomesh meshanid.srf meshanid.nt3m





















































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































