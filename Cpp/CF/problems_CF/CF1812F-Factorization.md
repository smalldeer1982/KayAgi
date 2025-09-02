---
title: "Factorization"
layout: "post"
diff: 难度0
pid: CF1812F
tag: []
---

# Factorization

## 题目描述

What is the largest prime factor of $ n $ ?

## 输入格式

The only line contains an integer $ n $ ( $ n = 4167792762229302596005813 $ or $ n = $ $ 5023266485352224530541666346579718188045725802556947855902702063768930526665237598287495728 $ $ 2186920039740245544313021979167491414627648054421626450903732301970386214502290904360792618 $ $ 5591029614599889902115472391135622402044979347133959392884686037208893694733655782993294168 $ $ 1679738555852317096830120847236770822731988661111203691013036774095229665675217827154840019 $ $ 9277276899311984129170278649605877582438144407974816241674549565633361834348720814779487433 $ $ 7933873576016717726298883519261055062303842274145012056670644839715140659887936321934474824 $ $ 687778512706909988484451300384818197143498259061041 $ ).

 
        $(function () {
            Codeforces.addMathJaxListener(function () {
                let $problem = $("div[problemindex=F]");
                let uuid = $problem.attr("data-uuid");
                let statementText = convertStatementToText($problem.find(".ttypography").get(0));

                let previousStatementText = Codeforces.getFromStorage(uuid);
                if (previousStatementText) {
                    if (previousStatementText !== statementText) {
                        $problem.find(".diff-notifier").show();

                        $problem.find(".diff-notifier-close").click(function() {
                            Codeforces.putToStorageTtl(uuid, statementText, 6 * 60 * 60);
                            $problem.find(".diff-notifier").hide();
                        });

                        $problem.find("a.view-changes").click(function() {
                            $.post("/data/diff", {action: "getDiff", a: previousStatementText, b: statementText}, function (result) {
                                if (result["success"] === "true") {
                                    Codeforces.facebox(".diff-popup", "https://codeforces.org/s/15363");
                                    $("#facebox .diff-popup").html(result["diff"]);
                                }
                            }, "json");
                        });
                    }
                } else {
                    Codeforces.putToStorageTtl(uuid, statementText, 6 * 60 * 60);
                }
            });
        });
     
    $(document).ready(function () {
        window.changedTests = new Set();

        function endsWith(string, suffix) {
            return string.indexOf(suffix, string.length - suffix.length) !== -1;
        }

        const inputFileDiv = $("div.input-file");
        const inputFile = inputFileDiv.text();
        const outputFileDiv = $("div.output-file");
        const outputFile = outputFileDiv.text();


        if (!endsWith(inputFile, "standard input")
            && !endsWith(inputFile, "standard input")) {
            inputFileDiv.attr("style", "font-weight: bold");
        }

        if (!endsWith(outputFile, "standard output")
            && !endsWith(outputFile, "standard output")) {
            outputFileDiv.attr("style", "font-weight: bold");
        }

        const titleDiv = $("div.header div.title");



        String.prototype.replaceAll = function (search, replace) {
            return this.split(search).join(replace);
        };

        $(".sample-test .title").each(function () {
            const preId = ("id" + Math.random()).replaceAll(".", "0");
            const cpyId = ("id" + Math.random()).replaceAll(".", "0");

            $(this).parent().find("pre").attr("id", preId);
            const $copy = $("

