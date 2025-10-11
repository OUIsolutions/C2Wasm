
function amalgamation_build()
  


    darwin.silverchain.generate({
        src = "src",
        project_short_cut = "c2wasm",
        tags = {  "macro", "em_js", "fdefine" }
    })


    local MAX_CONNTENT = darwin.camalgamator.ONE_MB * 20
    local MAX_RECURSION = 100

    local onefile = darwin.camalgamator.generate_amalgamation("src/one.c", MAX_CONNTENT, MAX_RECURSION)
    onefile = string.gsub(onefile,"//silver_chain_scope_start","")
    onefile = string.gsub(onefile,"//DONT MODIFY THIS COMMENT","")
    onefile = string.gsub(onefile,"//this import is computationally generated","")
    onefile = string.gsub(onefile,"//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain","")
    onefile = string.gsub(onefile,"//silver_chain_scope_end","")

    darwin.dtw.write_file("c2wasm.c",onefile)

end

darwin.add_recipe({
    name="amalgamation",
    description="make the c2wasm.c amalgamation file",
    outs={"c2wasm.c"},
    inputs={"src"},
    callback=amalgamation_build
})