/**
 * @author   service@ntfstool.com
 * Copyright (c) 2020 ntfstool.com
 * Copyright (c) 2020 alfw.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the MIT General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * MIT General Public License for more details.
 *
 * You should have received a copy of the MIT General Public License
 * along with this program (in the main directory of the NTFS Tool
 * distribution in the file COPYING); if not, write to the service@ntfstool.com
 */
"use strict"
var exec = require('child_process').exec;
var watch_bin = require("path").join(__dirname, "bin", "watch-mac")

const { spawn } = require('child_process')

function watchmac(path,callback) {
    var child = require('child_process').execFile(watch_bin, [path]);

    child.stdout.on('data', function(data) {
        var dataMap = data.toString().split("\n");
        for (var i in dataMap){
            var retMap = dataMap[i].split("\t").map(item => {
                return item.replace(path, "").trim();
            }).filter(function (data) {
                return data ? true : false;
            });

            if(retMap.length == 2){
                callback({
                    "Event":retMap[0],
                    "File":retMap[1],
                });
            }

            if(retMap.length == 3){
                callback({
                    "Event":retMap[0],
                    "File":retMap[1],
                    "From":retMap[1],
                    "To":retMap[1],
                });
            }
        }
    })
}

module.exports = watchmac;