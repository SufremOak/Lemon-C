const std = @import("std");

pub fn main() void {
    const args = std.process.args();
    if (args.len < 2) {
        std.debug.print("Usage: lemoc <command>\n", .{});
        return;
    }

    const command = args[1];
    switch (command) {
        "new" => createNewLemonfile(),
        "build" => buildLemonfile(),
        "parse" => parseFiles(),
        else => std.debug.print("Unknown command: {}\n", .{command}),
    }
}

fn createNewLemonfile() void {
    const fs = std.fs.cwd();
    const lemonfilePath = fs.path("Lemonfile");
    const mainFilePath = fs.path("main.🍋");

    if (fs.exists(lemonfilePath)) {
        std.debug.print("Lemonfile already exists. Please remove it or use a different name.\n", .{});
        return;
    }

    var lemonfile = try fs.createFile(lemonfilePath, .{});
    defer lemonfile.close();
    try lemonfile.writeAll("# Lemonfile\n");

    var mainFile = try fs.createFile(mainFilePath, .{});
    defer mainFile.close();
    try mainFile.writeAll("#include <Lemonade.hpp>\nLemon::Log(\"Hello, World!\");\n");

    std.debug.print("Lemonfile and main.🍋 created.\n", .{});
}

fn buildLemonfile() void {
    const fs = std.fs.cwd();
    const lemonfilePath = fs.path("Lemonfile");

    if (!fs.exists(lemonfilePath)) {
        std.debug.print("Lemonfile does not exist. Please create one first.\n", .{});
        return;
    }

    const result = std.process.exec(.{
        .argv = &[_][]const u8{"lemoc", "build", "Lemonfile"},
    });

    if (result) |exit_status| {
        if (exit_status != 0) {
            std.debug.print("Failed to build Lemonfile.\n", .{});
        } else {
            std.debug.print("Lemonfile built.\n", .{});
        }
    } else {
        std.debug.print("Failed to execute build command.\n", .{});
    }
}

fn parseFiles() void {
    const fs = std.fs.cwd();
    const lemonfilePath = fs.path("Lemonfile");
    const limaFilePath = fs.path("main.lima");

    if (fs.exists(lemonfilePath)) {
        parseFile(lemonfilePath);
    } else {
        std.debug.print("Lemonfile does not exist.\n", .{});
    }

    if (fs.exists(limaFilePath)) {
        parseFile(limaFilePath);
    } else {
        std.debug.print("main.lima file does not exist.\n", .{});
    }
}

fn parseFile(filePath: []const u8) void {
    const fs = std.fs.cwd();
    var file = try fs.openFile(filePath, .{ .read = true });
    defer file.close();

    var reader = file.reader();
    var buffer: [1024]u8 = undefined;
    while (true) {
        const readBytes = try reader.read(&buffer);
        if (readBytes == 0) break;
        std.debug.print("{s}", .{buffer[0..readBytes]});
    }
}
