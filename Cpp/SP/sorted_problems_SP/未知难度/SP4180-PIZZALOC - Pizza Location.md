---
title: "PIZZALOC - Pizza Location"
layout: "post"
diff: 难度0
pid: SP4180
tag: []
---

# PIZZALOC - Pizza Location

## 题目描述

 [English](/problems/PIZZALOC/en/) [Vietnamese](/problems/PIZZALOC/vn/)Our friend Picko is very reach and he wants to open lots of restaurants with delivery. The main food will be, of course, pizza. He has certain number of potential locations for the restaurants, and he knows the locations of the solitairs with lots of people which will often be his customers. Delivery of each restaurant will cover all the solitairs in given radius.

Picko can open only limited number of restaurants, and he wants that restaurants on the locations which will cover maximal number of people in solitairs.

Write a program that will calculate maximal number of people which we can cover with delivery.

## 输入格式

In the first line of the input file there are two integers K and R, separated with space, number of restaurants and radius of delivery, 1

In the second line there is integer M, number of locations, K

In each of the next M lines there are two integer X and Y, separated with space, coordinates of each location, -1000

In the next line there is integerN, number of solitairs, 1

In each of the next N lines there are three integers X, Y and S, separated with space, X and Y are coordinates of each solitaire, and S is number of people in that solitaire, -1000

We consider that solitaire is in radius of some restaurant if distance between them is less or equal to R. There are no two locations of restaurants on the same place.

## 输出格式

\> In only line of the output file we have to write maximal number from the text above.

