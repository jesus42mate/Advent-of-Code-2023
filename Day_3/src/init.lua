
local function init()
	local file_to_compile = "gear_ratios_alternative.c"
	local file_alias = "YEAH.out"

	print("trying to compile... ", file_to_compile)
	local command = "clang -o "..file_alias.." src/"..file_to_compile -- using string concatenation

	local exit_code = os.execute(command)
	if exit_code == true then
		print("Worked")
	else
		print("Failed to execute")
	end

	exit_code = os.execute("./YEAH.out")
end

init()

