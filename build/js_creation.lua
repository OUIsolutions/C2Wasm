

function create_js_part()
    local js_content = [[
let c2wasm = function(){
    let envcallbacks = {}
    let cfunctions = {}
    let main_obj = {
        envcallbacks: envcallbacks,
        cfunctions: cfunctions
    } 

]]
    local files = darwin.dtw.list_files_recursively("srcjs",true)
    for i=1,#files do
        local file = files[i]
        local content = darwin.dtw.load_file(file)
        js_content = js_content.."//"..file.."\n"
        js_content = js_content..content.."\n"
    end
    js_content = js_content.."return main_obj;"
    js_content = js_content.."}()\n"

    darwin.dtw.write_file("release/c2wasm.js",js_content)
end 