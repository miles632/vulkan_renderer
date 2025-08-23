GLSLC="/home/apu/vulkan/1.4.304.0/x86_64/bin/glslangValidator"
OUTDIR="shaders"

$GLSLC -V shaders/vertex.vert -o $OUTDIR/vert.spv
$GLSLC -V shaders/fragment.frag -o $OUTDIR/frag.spv

$GLSLC -V --target-env vulkan1.2 -S rgen shaders/raygen.rgen -o $OUTDIR/rgen.spv
