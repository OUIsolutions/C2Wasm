argv = function()


private_luargv =  {}
luargv = {}
private_lua_argv_string_functions = {}
-- file: src/luargv/base_flags.lua

luargv.get_flag_size = function(flags)
    if luargv.type(flags) == "string" then
        flags = { flags }
    end
    local total_found = 0
    local args_size = luargv.get_total_args_size()
    local capturing_flags = false
    for i = 1, args_size do
        local current = luargv.get_arg_by_index_not_adding_to_used(i)
        local possible_flag = private_luargv.get_formmated_flag_if_its_a_flag(current)
        if possible_flag then
            if private_luargv.is_inside(flags, possible_flag) then
                capturing_flags = true
            else
                capturing_flags = false
            end
        end

        if capturing_flags and not possible_flag then
            total_found = total_found + 1
        end
    end

    return total_found
end

luargv.get_flag_arg_by_index = function(flags, index, default)
    if luargv.type(flags) == "string" then
        flags = { flags }
    end
    local total_found = 0
    local args_size = luargv.get_total_args_size()
    local capturing_flags = false
    local possible_flag_index = nil
    for i = 1, args_size do
        local current = luargv.get_arg_by_index_not_adding_to_used(i)
        local possible_flag = private_luargv.get_formmated_flag_if_its_a_flag(current)
        if possible_flag then
            if private_luargv.is_inside(flags, possible_flag) then
                possible_flag_index = i
                capturing_flags = true
            else
                capturing_flags = false
            end
        end

        if capturing_flags and not possible_flag then
            total_found = total_found + 1
            if total_found == index then
                if possible_flag_index then
                    luargv.add_used_args_by_index(possible_flag_index)
                end
                luargv.add_used_args_by_index(i)
                return current
            end
        end
    end

    return default
end


luargv.flags_exist = function(flags)
    local args_size = luargv.get_total_args_size()

    for i = 1, args_size do
        local current = luargv.get_arg_by_index_not_adding_to_used(i)
        local possible_flag = private_luargv.get_formmated_flag_if_its_a_flag(current)
        if possible_flag then
            if private_luargv.is_inside(flags, possible_flag) then
                return true
            end
        end
    end
    return false
end

-- file: src/luargv/basic.lua

luargv.one_of_args_exist = function(args_list)
    if luargv.type(args_list) == "string" then
        args_list = { args_list }
    end
    for i = 1, #args_list do
        local arg_value = args_list[i]
        local size = luargv.get_total_args_size()
        for i = 1, size do
            local current = luargv.get_arg_by_index_not_adding_to_used(i)
            if current == arg_value then
                luargv.add_used_args_by_index(i)
                return true
            end
        end
        return false
    end
end

luargv.get_total_args_size = function()
    local count = 0
    for i = -3, 1000000 do
        local current = luargv.argslist[i]
        if current then
            count = count + 1
        end

        if i > 0 and current == nil then
            return count
        end
    end

    return 0
end

luargv.get_arg_by_index_not_adding_to_used = function(index)
    local decrementer = 0
    for i = 0, 1000000 do
        local converted_i = i * -1
        if luargv.argslist[converted_i] == nil then
            break
        end
        decrementer = decrementer + 1
    end
    return luargv.argslist[index - decrementer]
end

luargv.get_arg_by_index = function(index)
    luargv.add_used_args_by_index(index)
    return luargv.get_arg_by_index_not_adding_to_used(index)
end

-- file: src/luargv/compact_flag.lua

luargv.get_compact_flags = function(flags, index, default)
    local converted_flags = flags
    if luargv.type(flags) == "string" then
        ---@type string
        flags = flags
        flags = { flags }
    end


    local total = 0
    for i = 1, #flags do
        local flag_name = flags[i]
        local flag_size = luargv.get_str_size(flag_name)
        local args_size = luargv.get_total_args_size()
        for i = 1, args_size do
            local current = luargv.get_arg_by_index_not_adding_to_used(i)

            if private_luargv.starts_with(current, flag_name) then
                total = total + 1
                if total == index then
                    local current_size = luargv.get_str_size(current)
                    local formmated = luargv.substr_func(current, flag_size + 1, current_size)
                    luargv.add_used_args_by_index(i)
                    return formmated
                end
            end
        end
    end

    return default
end

luargv.get_compact_flags_size = function(flags)
    local converted_flags = flags
    if luargv.type(flags) == "string" then
     
        flags = { flags }
    end
    local total = 0
    for i = 1, #flags do
        local flag_name = flags[i]
        local flag_size = luargv.get_str_size(flag_name)
        local args_size = luargv.get_total_args_size()
        for i = 1, args_size do
            local current = luargv.get_arg_by_index_not_adding_to_used(i)

            if private_luargv.starts_with(current, flag_name) then
                total = total + 1
            end
        end
    end

    return total
end

-- file: src/luargv/constructor.lua

luargv.argslist = arg
luargv.flag_identifiers = { "-", "--" }
luargv.used_args = {}
if string then
    luargv.substr_func = string.sub
    luargv.get_str_size = string.len
end



luargv.type = type

if not luargv.get_str_size then
    luargv.get_str_size = function(str)
        return #str
    end
end

-- file: src/luargv/used_flags.lua

luargv.add_used_args_by_index = function(index)
    if index > luargv.get_total_args_size() then
        return
    end

    if not private_luargv.is_inside(luargv.used_args, index) then
        luargv.used_args[#luargv.used_args + 1] = index
    end
end

luargv.get_total_unused_args = function()
    return luargv.get_total_args_size() - #luargv.used_args
end

luargv.get_unsed_arg_by_index = function(index)
    local total       = 0
    local total_flags = luargv.get_total_args_size()
    for i = 1, total_flags do
        if not private_luargv.is_inside(luargv.used_args, i) then
            total = total + 1
            if total == index then
                return luargv.get_arg_by_index_not_adding_to_used(i)
            end
        end
    end
    return nil
end

luargv.get_next_unused_index = function()
    local total_flags = luargv.get_total_args_size()
    for i = 1, total_flags do
        if not private_luargv.is_inside(luargv.used_args, i) then
            return i
        end
    end
    return nil
end


luargv.get_next_unused = function()
    local i = luargv.get_next_unused_index()
    if i then
        return luargv.get_arg_by_index(i)
    end
end

-- file: src/private_luargv/algo.lua

private_luargv.starts_with = function(str, target)
    local target_size = luargv.get_str_size(target)
    local divided = luargv.substr_func(str, 1, target_size)

    if divided == target then
        return true
    end
    return false
end


private_luargv.get_array_size = function(array)
    local i     = 1
    local count = 0
    while array[i] do
        count = count + 1
        i = i + 1
    end
    return count
end

private_luargv.is_inside = function(array, item)
    local size = private_luargv.get_array_size(array)
    for i = 1, size do
        if array[i] == item then
            return true
        end
    end
    return false
end

-- file: src/private_luargv/formmated_flags.lua

private_luargv.get_formmated_flag_if_its_a_flag = function(current_arg)
    local total_flags = private_luargv.get_array_size(luargv.flag_identifiers)
    local chose_flag_size = 0
    for i = 1, total_flags do
        local current_flag = luargv.flag_identifiers[i]
        if private_luargv.starts_with(current_arg, current_flag) then
            local current_flag_size = luargv.get_str_size(current_flag)
            if current_flag_size >= chose_flag_size then
                chose_flag_size = current_flag_size
            end
        end
    end
    -- means its a flag
    if chose_flag_size > 0 then
        local args_size = luargv.get_str_size(current_arg)
        return luargv.substr_func(current_arg, chose_flag_size + 1, args_size)
    end
    return nil
end

-- file: src/types.lua

---@class Argv
---@field get_flag_size fun(flags:string[]|string):number
---@field get_flag_arg_by_index fun(flags:string[]|string,index:number,default:string | nil):string|nil
---@field flags_exist fun(flags:string[]):boolean
---@field one_of_args_exist fun(arg:string[] | string):boolean
---@field get_total_args_size fun():number
---@field get_arg_by_index_not_adding_to_used fun(index:number):string
---@field get_arg_by_index fun(index:number):string | nil
---@field get_compact_flags fun(flags:string[]|string,index,default:string | nil):string|nil
---@field get_compact_flags_size fun(flags:string[]|string):number
---@field used_args number[]
---@field type fun(value:any):string
---@field argslist string[]
---@field substr_func fun(str:string,start:number,endnum:number):string
---@field get_str_size fun(str:string):number
---@field flag_identifiers string[]
---@field add_used_args_by_index fun(used_flag:number)
---@field get_total_unused_args fun():number
---@field get_unsed_arg_by_index fun(index:number):string|nil
---@field get_next_unused_index fun():number|nil
---@field get_next_unused fun():string|nil


---@class PrivateArgv
---@field starts_with fun(str:string,target:string):boolean
---@field get_array_size fun(array:table):number
---@field is_inside fun(array:table,item:any):boolean
---@field get_formmated_flag_if_its_a_flag fun(current_arg:string):string |nil



---@type PrivateArgv
private_luargv = private_luargv


---@type Argv
luargv = luargv



---@type PrivateArgv
private_luargv = private_luargv


---@type Argv
luargv = luargv

return luargv
end
argv = argv()
ship = function()function PrivateDarwing_parse_to_bytes(seq)
    local buffer = {}
    for i = 1, #seq do
        buffer[#buffer + 1] = string.char(seq[i])
    end
    return buffer
end
PRIVATE_DARWIN_lua_ship_SO_INCLUDED = {}

private_lua_ship = {}
private_lua_ship_machine_methods = {}
if io then
    if io.open then
        private_lua_ship.open = io.open
    end
end
if os then
    if os.execute then
        private_lua_ship.os_execute = os.execute
    end
    if os.remove then
        private_lua_ship.os_remove = os.remove
    end
end
private_lua_ship.error = error

if string then
    private_lua_ship.string = string
end 
private_lua_ship.create_machine = function(start_image)
    local self_obj                = {}
    self_obj.provider             = "docker"
    self_obj.docker_file          = "FROM  " .. start_image .. "\n"
    self_obj.cache_folder         = "/tmp"
    self_obj.add_comptime_command = function(command)
        private_lua_ship_machine_methods.add_comptime_command(self_obj, command)
    end

    self_obj.add_runtime_command  = function(command)
        private_lua_ship_machine_methods.add_runtime_command(self_obj, command)
    end

    self_obj.copy                 = function(host_data, machine_dest)
        private_lua_ship_machine_methods.copy(self_obj, host_data, machine_dest)
    end

    self_obj.save_to_file         = function(filename)
        private_lua_ship_machine_methods.save_to_file(self_obj, filename)
    end

    self_obj.build                = function(name)
        return private_lua_ship_machine_methods.build(self_obj, name)
    end
    self_obj.start                = function(props)
        private_lua_ship_machine_methods.start(self_obj, props)
    end

    return self_obj
end

private_lua_ship_machine_methods.add_comptime_command = function(self_obj, command)
    self_obj.docker_file = self_obj.docker_file .. "RUN " .. command .. "\n"
end

private_lua_ship_machine_methods.add_runtime_command = function(self_obj, command)
    self_obj.docker_file = self_obj.docker_file .. "CMD " .. command .. "\n"
end

private_lua_ship_machine_methods.env = function(self_obj, key, value)
    self_obj.docker_file = self_obj.docker_file .. "ENV " .. key .. " " .. value .. "\n"
end

private_lua_ship_machine_methods.copy = function(self_obj, host_data, machine_dest)
    self_obj.docker_file = self_obj.docker_file .. "COPY " .. host_data .. " " .. machine_dest .. "\n"
end

private_lua_ship_machine_methods.save_to_file = function(self_obj, filename)
    private_lua_ship.open(filename, "w"):write(self_obj.docker_file):close()
end

private_lua_ship_machine_methods.build        = function(self_obj, name)
    if not name then
        name = "sha" .. private_lua_ship.sha256(self_obj.docker_file)
    end
    local filename = self_obj.cache_folder .. "/" .. name .. ".Dockerfile"
    private_lua_ship_machine_methods.save_to_file(self_obj, filename)
    local command = self_obj.provider .. " build -t " .. name .. " -f " .. filename .. " .  --quiet   "
    local ok = private_lua_ship.os_execute(command)
    if not ok then
        private_lua_ship.error("unable to execute command:\n" .. command)
    end
    private_lua_ship.os_remove(filename)
    return name
end
private_lua_ship_machine_methods.start        = function(self_obj, props)
    if not props.rebuild then
        props.rebuild = true
    end
    local name = props.name
    if props.rebuild then
        name = private_lua_ship_machine_methods.build(self_obj, props.name)
    end
    if not props.flags then
        props.flags = {}
    end
    local command = self_obj.provider .. " run "
    for i = 1, #props.flags do
        local current_flag = props.flags[i]
        command = command .. current_flag .. " "
    end

    if not props.volumes then
        props.volumes = {}
    end
    for i = 1, #props.volumes do
        local current_volume = props.volumes[i]
        command = command .. "-v " .. current_volume[1] .. ":" .. current_volume[2] .. ":z "
    end
    command = command .. name
    if props.command then

        local format_command = function(command_props)
            local formmated_command = ""
            if type(command_props) == "string" then
                formmated_command = private_lua_ship.string.gsub(command_props, '"', '\\"')
            end
            return formmated_command
        end

        local formmated = format_command(props.command)

        if type(props.command) == "table" then
            local concat = ""
            for i=1, #props.command do
                if i > 1 then
                    concat = " && "
                end
                formmated = formmated .. concat ..  format_command(props.command[i])
            end

        end

        command = command .. ' sh -c "' .. formmated .. '"'
    end
    local ok = private_lua_ship.os_execute(command)
    if not ok then
        private_lua_ship.error("unable to execute command:\n" .. command)
    end
end

--[[
  Author: OGabrieLima
  GitHub: https://github.com/OGabrieLima
  Discord: ogabrielima
  Description: This is a Lua script that implements the SHA-256 algorithm to calculate the hash of a message.
               It includes a helper function for right rotation (bitwise) and the main function `sha256`.
               The `sha256` function can be used to calculate the SHA-256 hash of a message.
  Creation Date: 2024-04-08
]]

-- Auxiliary function: right rotation (bitwise)
local function bit_ror(x, y)
    return ((x >> y) | (x << (32 - y))) & 0xFFFFFFFF
end

-- Main function: SHA256
private_lua_ship.sha256 = function(message)
    local k = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    }

    local function preprocess(message)
        local len = #message
        local bitLen = len * 8
        message = message .. "\128" -- append single '1' bit

        local zeroPad = 64 - ((len + 9) % 64)
        if zeroPad ~= 64 then
            message = message .. string.rep("\0", zeroPad)
        end

        -- append length
        message = message .. string.char(
            bitLen >> 56 & 0xFF,
            bitLen >> 48 & 0xFF,
            bitLen >> 40 & 0xFF,
            bitLen >> 32 & 0xFF,
            bitLen >> 24 & 0xFF,
            bitLen >> 16 & 0xFF,
            bitLen >> 8 & 0xFF,
            bitLen & 0xFF
        )

        return message
    end

    local function chunkify(message)
        local chunks = {}
        for i = 1, #message, 64 do
            table.insert(chunks, message:sub(i, i + 63))
        end
        return chunks
    end

    local function processChunk(chunk, hash)
        local w = {}

        for i = 1, 64 do
            if i <= 16 then
                w[i] = string.byte(chunk, (i - 1) * 4 + 1) << 24 |
                    string.byte(chunk, (i - 1) * 4 + 2) << 16 |
                    string.byte(chunk, (i - 1) * 4 + 3) << 8 |
                    string.byte(chunk, (i - 1) * 4 + 4)
            else
                local s0 = bit_ror(w[i - 15], 7) ~ bit_ror(w[i - 15], 18) ~ (w[i - 15] >> 3)
                local s1 = bit_ror(w[i - 2], 17) ~ bit_ror(w[i - 2], 19) ~ (w[i - 2] >> 10)
                w[i] = (w[i - 16] + s0 + w[i - 7] + s1) & 0xFFFFFFFF
            end
        end

        local a, b, c, d, e, f, g, h = table.unpack(hash)

        for i = 1, 64 do
            local s1 = bit_ror(e, 6) ~ bit_ror(e, 11) ~ bit_ror(e, 25)
            local ch = (e & f) ~ ((~e) & g)
            local temp1 = (h + s1 + ch + k[i] + w[i]) & 0xFFFFFFFF
            local s0 = bit_ror(a, 2) ~ bit_ror(a, 13) ~ bit_ror(a, 22)
            local maj = (a & b) ~ (a & c) ~ (b & c)
            local temp2 = (s0 + maj) & 0xFFFFFFFF

            h = g
            g = f
            f = e
            e = (d + temp1) & 0xFFFFFFFF
            d = c
            c = b
            b = a
            a = (temp1 + temp2) & 0xFFFFFFFF
        end

        return (hash[1] + a) & 0xFFFFFFFF,
            (hash[2] + b) & 0xFFFFFFFF,
            (hash[3] + c) & 0xFFFFFFFF,
            (hash[4] + d) & 0xFFFFFFFF,
            (hash[5] + e) & 0xFFFFFFFF,
            (hash[6] + f) & 0xFFFFFFFF,
            (hash[7] + g) & 0xFFFFFFFF,
            (hash[8] + h) & 0xFFFFFFFF
    end

    message = preprocess(message)
    local chunks = chunkify(message)

    local hash = { 0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19 }
    for _, chunk in ipairs(chunks) do
        hash = { processChunk(chunk, hash) }
    end

    local result = ""
    for _, h in ipairs(hash) do
        result = result .. string.format("%08x", h)
    end

    return result
end

return private_lua_ship
---@class LuaShipStartProps
---@class flags string[]
---@class volumes string[]string[]
---@class command string


---@class LuaShipMachine
---@field provider "podman"| "docker"
---@field docker_file string
---@field add_comptime_command fun(command:string)
---@field copy fun(host_data:string,dest_data:string)
---@field env fun(name:string,value:string)
---@field save_to_file fun(filename:string)
---@field start fun(props:LuaShipStartProps)


---@class LuaShip
---@field create_machine fun(distro:string):LuaShipMachine
---@field open fun(filename:string,mode:string)
---@field os_execute fun(command:string):boolean
---@field os_remove fun(filename:string)
---@field error fun(errror:string)
end
ship = ship()


GREEN = "\27[0;32m"
BLUE = "\27[0;34m"
YELLOW = "\27[0;33m"
RED = "\27[0;31m"
RESET = "\27[0m"
PURPLE = "\27[0;35m"




function newLLM(permissions)
    local llm = newRawLLM()
    local old_generate = llm.generate
    local files = {}
    if type(permissions) ~= "table" then
        error("permissions must be a table")
    end


    local validPermissions = {
        "read",
        "write",
        "execute",
        "delete",
        "list"
    }
    for _, permission in ipairs(permissions) do
        if not table.contains(validPermissions, permission) then
            error("Invalid permission: " .. permission)
        end
        if type(permission) ~= "boolean" then
            error("Permission must be a boolean")
        end
    end
    
    llm.add_file = function(filename)
        files[#files + 1] = {filename = filename,already_added = false}
    end

    llm.add_dir = function(dir)
        local concat_path = true
        local dir_files = dtw.list_files_recursively(dir,concat_path)
        for _, file in ipairs(dir_files) do
            files[#files + 1] = {filename = file,already_added = false}
        end
    end
    llm.generate = function()
        local content = ""
        for _, file in ipairs(files) do
            if not file.already_added then
                local file_content = dtw.load_file(file.filename)
                if file_content == nil then
                    error("File not found: " .. file.filename)
                    return
                end
                content = content.."file: " .. file.filename .. "\n" .. file_content .. "\n"
                file.already_added = true
            end
        end
        if content ~= "" then
            llm.add_user_prompt(content)
        end
        return old_generate()
    end
       

    if permissions.read then

        local args = {
            {name = "file",description="the file name", type = "string", required = true},
        }
        local callback = function(args)
            print(YELLOW.."Reading file: "..args.file..RESET)
            return dtw.load_file(args.file)
        end
        llm.add_function("read", "read a file and return the content of the file",args,callback)
    end
    if permissions.write then
        local args = {
            {name = "file",description="the file name", type = "string", required = true},
            {name = "content",description="the content to write", type = "string", required = true},
        }
        local callback = function(args)
            print(YELLOW.."Writing file: "..args.file..RESET)
            dtw.write_file(args.file, args.content)
            return "file written"
        end
        llm.add_function("write", "write a file and return the content of the file",args,callback)
    end
    if permissions.execute then
        local args = {
            {name = "command",description="the command to execute", type = "string", required = true},
        }
        local callback = function(args)
            print(YELLOW.."Executing command: "..args.command..RESET)
            return os.execute(args.command)
        end
        llm.add_function("execute", "execute a command and return the output",args,callback)

    end
    if permissions.delete then
        local args = {
            {name = "element",description="the element to remove", type = "string", required = true},
        }
        local callback = function(args)
            print(YELLOW.."Deleting element: "..args.element..RESET)
            dtw.remove_any(args.element)
            return "element removed"
        end
        llm.add_function("delete", "delete a file or a dir",args,callback)
    end



    if permissions.list then
        local args = {
            {name = "dir",description="the directory to list", type = "string", required = true},
        }
        local callback = function(args)
            print(YELLOW.."Listing directory: "..args.dir..RESET)
            local files ,size= dtw.list_files_recursively(args.dir)
            return files
        end
        llm.add_function("list", "list a directory and return the content of the directory",args,callback)
    end


  return llm


end 
