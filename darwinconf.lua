darwin.silverchain.generate({
    src = "src",
    project_short_cut = "c2wasm",
    tags = {  "macro", "em_js", "fdefine" }
})


local MAX_CONNTENT = darwin.camalgamator.ONE_MB * 20
local MAX_RECURSION = 100

local onefile = darwin.camalgamator.generate_amalgamation("src/one.c", MAX_CONNTENT, MAX_RECURSION)

darwin.dtw.write_file("c2wasm.c",onefile)