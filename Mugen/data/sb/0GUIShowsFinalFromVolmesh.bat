REM Now open generated nt3m for visual inspection
REM NOTE: in the GUI, choose View -> Draw Boundary Tensors
REM  --resamplefieldontomesh meshanid.srf meshanid.nt3m ^  



REM tensorhex.exe --geom meshanid.srf --bgmesh meshanid.srf --initfield ^

tensorhex.exe --geom meshanid.srf --bgmesh meshanid.srf --initsurfacefield ^
  --loadfield meshanid.nt3m --persevere --gui
  
  
