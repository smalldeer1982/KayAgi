---
title: "Sonya and Hotels"
layout: "post"
diff: 普及-
pid: CF1004A
tag: ['枚举', '概率论']
---

# Sonya and Hotels

## 题目描述

Sonya decided that having her own hotel business is the best way of earning money because she can profit and rest wherever she wants.

The country where Sonya lives is an endless line. There is a city in each integer coordinate on this line. She has $ n $ hotels, where the $ i $ -th hotel is located in the city with coordinate $ x_i $ . Sonya is a smart girl, so she does not open two or more hotels in the same city.

Sonya understands that her business needs to be expanded by opening new hotels, so she decides to build one more. She wants to make the minimum distance from this hotel to all others to be equal to $ d $ . The girl understands that there are many possible locations to construct such a hotel. Thus she wants to know the number of possible coordinates of the cities where she can build a new hotel.

Because Sonya is lounging in a jacuzzi in one of her hotels, she is asking you to find the number of cities where she can build a new hotel so that the minimum distance from the original $ n $ hotels to the new one is equal to $ d $ .

## 输入格式

The first line contains two integers $ n $ and $ d $ ( $ 1\leq n\leq 100 $ , $ 1\leq d\leq 10^9 $ ) — the number of Sonya's hotels and the needed minimum distance from a new hotel to all others.

The second line contains $ n $ different integers in strictly increasing order $ x_1, x_2, \ldots, x_n $ ( $ -10^9\leq x_i\leq 10^9 $ ) — coordinates of Sonya's hotels.

## 输出格式

Print the number of cities where Sonya can build a new hotel so that the minimum distance from this hotel to all others is equal to $ d $ .

## 说明/提示

In the first example, there are $ 6 $ possible cities where Sonya can build a hotel. These cities have coordinates $ -6 $ , $ 5 $ , $ 6 $ , $ 12 $ , $ 13 $ , and $ 19 $ .

In the second example, there are $ 5 $ possible cities where Sonya can build a hotel. These cities have coordinates $ 2 $ , $ 6 $ , $ 13 $ , $ 16 $ , and $ 21 $ .

## 样例 #1

### 输入

```
4 3
-3 2 9 16

```

### 输出

```
6

```

## 样例 #2

### 输入

```
5 2
4 8 11 18 19

```

### 输出

```
5

```



---

---
title: "Homework"
layout: "post"
diff: 普及-
pid: CF101A
tag: ['贪心', '排序', '概率论']
---

# Homework

## 题目描述

Gerald在上学的一天，他的老师在班上布置了一项作业：她给每个同学一个有n个小写拉丁字母（即英文字母）的字符串，要求学生学习这个字符串中的字母的写法。但是，由于Gerald太懒了，他不想学习这些字母。这就是为什么他决定丢掉这个字符串的部分（不需要是连续的一部分）。他所丢失的部分可以由若干个任意长度在任意位置的连续的子字符串组成。但是，Gerald知道，如果他丢掉了超过k个字母，他就会显得非常可疑。

请求出在不超过k个字母被删除之后，字符串中最少剩下多少个不同的字母。你还需要求出一种删除这些字母的方式。

## 输入格式

输入的第一行是一个长度为n的字符串( $1<=n<=10^{5}$ )。这个字符串由小写拉丁字母组成。输入的第二行是数k( $0<=k<=10^{5}$ )。

## 输出格式

请在第一行只输出数m——从这个字符串中删除k个字符之后最少剩下的最少的不同字母的个数。

在第二行输出在删除一些字母之后Gerald所能得到的字符串。这个字符串应该刚好有m个不同的字母。这个最终的字符串应该是原字符串的一个子串。如果Gerald能够得到多个都刚好有m个不同字母的不同的字符串，输出其中任意一个。

## 说明/提示

在第一个样例中这个字符串含有5个字母但是你只允许删去其中4个，所以会剩下至少一个字母。所以，正确答案就是1和任意一个长度在1到5的、只含有字母a的字符串。

在第二个杨立忠你可以删去4个字母。你不能删去所有的字母，因为这个字符串的长度是7。 但是，你可以删去所以除了a以外的字母（这样的字母不多于4个），所以得到的答案是"aaaa"。

在第三个样例中字符串的长度是8，且k=10，所以可以将所有的字母都删去。正确答案是0和空字符串。

Translated by @oolliivveerr

## 样例 #1

### 输入

```
aaaaa
4

```

### 输出

```
1
aaaaa

```

## 样例 #2

### 输入

```
abacaba
4

```

### 输出

```
1
aaaa

```

## 样例 #3

### 输入

```
abcdefgh
10

```

### 输出

```
0


```



---

---
title: "Doggo Recoloring"
layout: "post"
diff: 普及-
pid: CF1025A
tag: ['模拟', '概率论']
---

# Doggo Recoloring

## 题目描述

Panic is rising in the committee for doggo standardization — the puppies of the new brood have been born multi-colored! In total there are 26 possible colors of puppies in the nature and they are denoted by letters from 'a' to 'z' inclusive.

The committee rules strictly prohibit even the smallest diversity between doggos and hence all the puppies should be of the same color. Thus Slava, the committee employee, has been assigned the task to recolor some puppies into other colors in order to eliminate the difference and make all the puppies have one common color.

Unfortunately, due to bureaucratic reasons and restricted budget, there's only one operation Slava can perform: he can choose a color $ x $ such that there are currently at least two puppies of color $ x $ and recolor all puppies of the color $ x $ into some arbitrary color $ y $ . Luckily, this operation can be applied multiple times (including zero).

For example, if the number of puppies is $ 7 $ and their colors are represented as the string "abababc", then in one operation Slava can get the results "zbzbzbc", "bbbbbbc", "aaaaaac", "acacacc" and others. However, if the current color sequence is "abababc", then he can't choose $ x $ ='c' right now, because currently only one puppy has the color 'c'.

Help Slava and the committee determine whether it is possible to standardize all the puppies, i.e. after Slava's operations all the puppies should have the same color.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the number of puppies.

The second line contains a string $ s $ of length $ n $ consisting of lowercase Latin letters, where the $ i $ -th symbol denotes the $ i $ -th puppy's color.

## 输出格式

If it's possible to recolor all puppies into one color, print "Yes".

Otherwise print "No".

Output the answer without quotation signs.

## 说明/提示

In the first example Slava can perform the following steps:

1. take all puppies of color 'a' (a total of two) and recolor them into 'b';
2. take all puppies of color 'd' (a total of two) and recolor them into 'c';
3. take all puppies of color 'b' (three puppies for now) and recolor them into 'c'.

In the second example it's impossible to recolor any of the puppies.

In the third example all the puppies' colors are the same; thus there's no need to recolor anything.

## 样例 #1

### 输入

```
6
aabddc

```

### 输出

```
Yes

```

## 样例 #2

### 输入

```
3
abc

```

### 输出

```
No

```

## 样例 #3

### 输入

```
3
jjj

```

### 输出

```
Yes

```



---

---
title: "Heist"
layout: "post"
diff: 普及-
pid: CF1041A
tag: ['枚举', '排序', '概率论']
---

# Heist

## 题目描述

昨晚有一家电子商店被抢劫了。

昨天在商店里的所有键盘都是从$x$开始按升序编号的。例如，如果$x=4$，并且商店中有$3$个键盘，那么编号就为$4,5,6$；如果$x=10$，并且有$7$个键盘，那么编号就为$10,11,12,13,14,15,16$。

在抢劫之后，只有$n$个键盘仍然存在，他们的编号分别为$a_1,a_2,\dots ,a_n$。计算被盗的键盘的最小可能数量。工作人员不记得$x$也不记得商店里原来有几个键盘。

## 输入格式

第一行输入一个整数$n(1\le n\le 1000)$，为商店里仍然存在的键盘的数量。

第二行输入$n$个整数$a_1,a_2\dots ,a_n(1\le a_i\le 10^9)$，表示所有商店里仍然存在的键盘的编号。

## 输出格式

输出被盗的键盘的最小可能数量。

感谢@dblark 提供的翻译

## 样例 #1

### 输入

```
4
10 13 12 8

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5
7 5 6 4 8

```

### 输出

```
0

```



---

---
title: "Oh Those Palindromes"
layout: "post"
diff: 普及-
pid: CF1063A
tag: ['字符串', '概率论', '构造']
---

# Oh Those Palindromes

## 题目描述

一个非空字符串叫做回文串。如果它从左到右，从右到左读相同，那么它就是回文串。
例如，“ABCBA”,“A”和“ABBA”都是回文串，而“ABAB”和“XY”则不是。




如果可以通过从字符串的开头和结尾删除一些（可能为零）字符来从该字符串获得新字符串，
则新字符串叫做另一个字符串的子字符串。
例如，“ABC”、“AB”和“C”是字符串“ABC”的子串，而“AC”和“D”不是。


我们把字符串的“回文计数”定义为回文的子串个数。
例如，字符串“aaa”的回文计数是6，因为它的所有子字符串都是回文，
而字符串“abc”的回文计数是3，因为只有长度为1的子字符串是回文。


给你一个字符串S。你可以任意地重新排列它的字符，求它的回文计数最大值。

## 输入格式

第一行包含整数n（1≤n≤100000）表示字符串s的长度。




第二行包含字符串S，它由n个小写字母组成。

## 输出格式

输出字符串t，（它是字符串s的一种排列）
此外，t应该具有最大回文计数的可能值。




如果有多个这样的字符串，输出它们中的任何一个。

## 输入输出样例：
#### 输入样例#1：
```
5
oolol
```
#### 输出样例#1：
```
ololo
```

#### 输入样例#2：
```
16
gagadbcgghhchbdf
```
#### 输出样例#2：
```
16
gagadbcgghhchbdf
```

## 说明/提示

在第一个例子中，字符串“ololo”有9个9回文子串：
"o","l","o","l","o","olo","lol","olo","oloo"

注意，即使某些子串重合，它们也会在生成的字符串中计入多次。




在第二个例子中，字符串“abccbaghghghgdfd”的回文计数为29。

## 样例 #1

### 输入

```
5
oolol

```

### 输出

```
ololo

```

## 样例 #2

### 输入

```
16
gagadbcgghhchbdf

```

### 输出

```
abccbaghghghgdfd

```



---

---
title: "Diverse Substring"
layout: "post"
diff: 普及-
pid: CF1073A
tag: ['字符串', '枚举', '概率论']
---

# Diverse Substring

## 题目描述

You are given a string $ s $ , consisting of $ n $ lowercase Latin letters.

A substring of string $ s $ is a continuous segment of letters from $ s $ . For example, "defor" is a substring of "codeforces" and "fors" is not.

The length of the substring is the number of letters in it.

Let's call some string of length $ n $ diverse if and only if there is no letter to appear strictly more than $ \frac n 2 $ times. For example, strings "abc" and "iltlml" are diverse and strings "aab" and "zz" are not.

Your task is to find any diverse substring of string $ s $ or report that there is none. Note that it is not required to maximize or minimize the length of the resulting substring.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 1000 $ ) — the length of string $ s $ .

The second line is the string $ s $ , consisting of exactly $ n $ lowercase Latin letters.

## 输出格式

Print "NO" if there is no diverse substring in the string $ s $ .

Otherwise the first line should contain "YES". The second line should contain any diverse substring of string $ s $ .

## 说明/提示

The first example has lots of correct answers.

Please, restrain yourself from asking if some specific answer is correct for some specific test or not, these questions always lead to "No comments" answer.

## 样例 #1

### 输入

```
10
codeforces

```

### 输出

```
YES
code

```

## 样例 #2

### 输入

```
5
aaaaa

```

### 输出

```
NO

```



---

---
title: "Marks"
layout: "post"
diff: 普及-
pid: CF152A
tag: ['概率论']
---

# Marks

## 题目描述

总的来说，这个小组有$N$个学生。他们获得了$M$科目的分数。每个学生从每个科目的$1$分到$9$分（包括$1$分）得了一分。

如果没有学生在这个科目上获得更高的分数，我们就可以认为这个学科这个学生是最擅长的。如果存在一个他最擅长的学科，那么这个学生就是成功的。

你的任务是找出小组中成功学生的人数。

## 输入格式

第一个输入行包含两个整数$N$和$M$（$1\leq N,M\leq100$）— 对应学生的数量和科目的数目。接下来的$N$行每行包含$M$个字符描述的成绩单。在成绩单中每个字符是一个从$1$到$9$的数字。值得注意的是，这些数字没有被空格分开。

## 输出格式

输出一个数字 — 在被给的这个小组中最好的学生的数量

## 说明/提示

在第一个样例中，$1$号学生是最好的科目是$1$和$3$，$2$号学生是最好的科目$1$和$2$，但$3$号学生没有任何科目最好。

在第二个样例中，每个学生至少有一个科目是最好的。

Translated by Khassar

## 样例 #1

### 输入

```
3 3
223
232
112

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3 5
91728
11828
11111

```

### 输出

```
3

```



---

---
title: "Opponents"
layout: "post"
diff: 普及-
pid: CF688A
tag: ['模拟', '贪心', '概率论']
---

# Opponents

## 题目描述

# 问题描述

小白有 n 个对手，他每天都要和这些对手PK。对于每一天，如果 n 个对手全部到齐，那么小白就输了一场，否则小白就赢了一场。特别的，如果某天一个对手都没有到，也算小白赢。现在已知对手 d 天的出场情况，请计算小白最多能连胜多少场。

## 输入格式

第一行，两个整数 n , d ( 1 ≤ n,d ≤ 100 )。接下来 d 行，每行 n 个 0 或 1 的整数，依次表示这一天所有对手的到场情况， 1 表示到场， 0 表示缺席。

## 输出格式

一个整数，表示最多的连胜场次。

## 样例 #1

### 输入

```
2 2
10
00

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4 1
0100

```

### 输出

```
1

```

## 样例 #3

### 输入

```
4 5
1101
1111
0110
1011
1111

```

### 输出

```
2

```



---

---
title: "President's Office"
layout: "post"
diff: 普及-
pid: CF6B
tag: ['搜索', '深度优先搜索 DFS', '概率论']
---

# President's Office

## 输入格式

第一行：

房间长n,宽m,总统办公桌代表的字符串

接下来2 ~ n+1行,每行输入m列:

房间内的办公桌的颜色（大写字母）。"."为空单元格。

## 输出格式

一行一个变量：

求出在总统桌四周相邻的办公桌数量
样例1 解释：

3 4 R

G . B .

. R R .

T T T .

此办公室的总统桌在二排的第二，三列（连起来的并且颜色相同算一个办公桌，此样例总统桌面积为1*2）

那么四周则有办公桌：

TTT（TTT面积为1*3）

B

因此输出2
Translated by @s5_gan

## 样例 #1

### 输入

```
3 4 R
G.B.
.RR.
TTT.

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3 3 Z
...
.H.
..Z

```

### 输出

```
0

```



---

---
title: "Memory and Trident"
layout: "post"
diff: 普及-
pid: CF712B
tag: ['概率论']
---

# Memory and Trident

## 题目描述

Memory is performing a walk on the two-dimensional plane, starting at the origin. He is given a string $ s $ with his directions for motion:

- An 'L' indicates he should move one unit left.
- An 'R' indicates he should move one unit right.
- A 'U' indicates he should move one unit up.
- A 'D' indicates he should move one unit down.

But now Memory wants to end at the origin. To do this, he has a special trident. This trident can replace any character in $ s $ with any of 'L', 'R', 'U', or 'D'. However, because he doesn't want to wear out the trident, he wants to make the minimum number of edits possible. Please tell Memory what is the minimum number of changes he needs to make to produce a string that, when walked, will end at the origin, or if there is no such string.

## 输入格式

The first and only line contains the string $ s $ ( $ 1<=|s|<=100000 $ ) — the instructions Memory is given.

## 输出格式

If there is a string satisfying the conditions, output a single integer — the minimum number of edits required. In case it's not possible to change the sequence in such a way that it will bring Memory to to the origin, output -1.

## 说明/提示

In the first sample test, Memory is told to walk right, then right, then up. It is easy to see that it is impossible to edit these instructions to form a valid walk.

In the second sample test, Memory is told to walk up, then down, then up, then right. One possible solution is to change $ s $ to "LDUR". This string uses 1 edit, which is the minimum possible. It also ends at the origin.

## 样例 #1

### 输入

```
RRU

```

### 输出

```
-1

```

## 样例 #2

### 输入

```
UDUR

```

### 输出

```
1

```

## 样例 #3

### 输入

```
RUUR

```

### 输出

```
2

```



---

---
title: "Gotta Catch Em' All!"
layout: "post"
diff: 普及-
pid: CF757A
tag: ['字符串', '概率论']
---

# Gotta Catch Em' All!

## 题目描述

Bash wants to become a Pokemon master one day. Although he liked a lot of Pokemon, he has always been fascinated by Bulbasaur the most. Soon, things started getting serious and his fascination turned into an obsession. Since he is too young to go out and catch Bulbasaur, he came up with his own way of catching a Bulbasaur.

Each day, he takes the front page of the newspaper. He cuts out the letters one at a time, from anywhere on the front page of the newspaper to form the word "Bulbasaur" (without quotes) and sticks it on his wall. Bash is very particular about case — the first letter of "Bulbasaur" must be upper case and the rest must be lower case. By doing this he thinks he has caught one Bulbasaur. He then repeats this step on the left over part of the newspaper. He keeps doing this until it is not possible to form the word "Bulbasaur" from the newspaper.

Given the text on the front page of the newspaper, can you tell how many Bulbasaurs he will catch today?

Note: uppercase and lowercase letters are considered different.

## 输入格式

Input contains a single line containing a string $ s $ ( $ 1<=|s|<=10^{5} $ ) — the text on the front page of the newspaper without spaces and punctuation marks. $ |s| $ is the length of the string $ s $ .

The string $ s $ contains lowercase and uppercase English letters, i.e. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF757A/5a3118f39129b2a74b924e2ddab1fc42162a4073.png).

## 输出格式

Output a single integer, the answer to the problem.

## 说明/提示

In the first case, you could pick: Bulbbasaur.

In the second case, there is no way to pick even a single Bulbasaur.

In the third case, you can rearrange the string to BulbasaurBulbasauraddrgndgddgargndbb to get two words "Bulbasaur".

## 样例 #1

### 输入

```
Bulbbasaur

```

### 输出

```
1

```

## 样例 #2

### 输入

```
F

```

### 输出

```
0

```

## 样例 #3

### 输入

```
aBddulbasaurrgndgbualdBdsagaurrgndbb

```

### 输出

```
2

```



---

---
title: "Mike and palindrome"
layout: "post"
diff: 普及-
pid: CF798A
tag: ['模拟', '字符串', '概率论']
---

# Mike and palindrome

## 题目描述

麦克有一个只有小写英文字母的字符串 _s_ 。他想通过改变一个字符 的方式来让整个字符串成为回文字符串。

回文字符串是一个正着读和反着读都一样的字符串。比如说"z"， "aaa"，"aba"， "abccba"是回文字符串，而"codeforces"， "reality"和"ab"不是回文字符串。

## 输入格式

一行，包括一个字符串 _s_ (1<=|s|<=15)。

## 输出格式

如果麦克能通过只改变一个字符就使整个字符串成回文字符串的话就输出"YES"(不包括双引号)，不然的话就输出"NO"(同样不包括双引号)

感谢@deadpool123  提供的翻译

## 样例 #1

### 输入

```
abccaa

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
abbcca

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
abcda

```

### 输出

```
YES

```



---

---
title: "Kalevitch and Chess"
layout: "post"
diff: 普及-
pid: CF7A
tag: ['模拟', '贪心', '概率论']
---

# Kalevitch and Chess

## 题目描述

A famous Berland's painter Kalevitch likes to shock the public. One of his last obsessions is chess. For more than a thousand years people have been playing this old game on uninteresting, monotonous boards. Kalevitch decided to put an end to this tradition and to introduce a new attitude to chessboards.

As before, the chessboard is a square-checkered board with the squares arranged in a $ 8×8 $ grid, each square is painted black or white. Kalevitch suggests that chessboards should be painted in the following manner: there should be chosen a horizontal or a vertical line of 8 squares (i.e. a row or a column), and painted black. Initially the whole chessboard is white, and it can be painted in the above described way one or more times. It is allowed to paint a square many times, but after the first time it does not change its colour any more and remains black. Kalevitch paints chessboards neatly, and it is impossible to judge by an individual square if it was painted with a vertical or a horizontal stroke.

Kalevitch hopes that such chessboards will gain popularity, and he will be commissioned to paint chessboards, which will help him ensure a comfortable old age. The clients will inform him what chessboard they want to have, and the painter will paint a white chessboard meeting the client's requirements.

It goes without saying that in such business one should economize on everything — for each commission he wants to know the minimum amount of strokes that he has to paint to fulfill the client's needs. You are asked to help Kalevitch with this task.

## 输入格式

The input file contains 8 lines, each of the lines contains 8 characters. The given matrix describes the client's requirements, W character stands for a white square, and B character — for a square painted black.

It is guaranteed that client's requirments can be fulfilled with a sequence of allowed strokes (vertical/column or horizontal/row).

## 输出格式

Output the only number — the minimum amount of rows and columns that Kalevitch has to paint on the white chessboard to meet the client's requirements.

## 样例 #1

### 输入

```
WWWBWWBW
BBBBBBBB
WWWBWWBW
WWWBWWBW
WWWBWWBW
WWWBWWBW
WWWBWWBW
WWWBWWBW

```

### 输出

```
3

```

## 样例 #2

### 输入

```
WWWWWWWW
BBBBBBBB
WWWWWWWW
WWWWWWWW
WWWWWWWW
WWWWWWWW
WWWWWWWW
WWWWWWWW

```

### 输出

```
1

```



---

---
title: "Tricky Alchemy"
layout: "post"
diff: 普及-
pid: CF912A
tag: ['模拟', '数学', '概率论']
---

# Tricky Alchemy

## 题目描述

During the winter holidays, the demand for Christmas balls is exceptionally high. Since it's already $ 2018 $ , the advances in alchemy allow easy and efficient ball creation by utilizing magic crystals.

Grisha needs to obtain some yellow, green and blue balls. It's known that to produce a yellow ball one needs two yellow crystals, green — one yellow and one blue, and for a blue ball, three blue crystals are enough.

Right now there are $ A $ yellow and $ B $ blue crystals in Grisha's disposal. Find out how many additional crystals he should acquire in order to produce the required number of balls.

## 输入格式

The first line features two integers $ A $ and $ B $ ( $ 0<=A,B<=10^{9} $ ), denoting the number of yellow and blue crystals respectively at Grisha's disposal.

The next line contains three integers $ x $ , $ y $ and $ z $ ( $ 0<=x,y,z<=10^{9} $ ) — the respective amounts of yellow, green and blue balls to be obtained.

## 输出格式

Print a single integer — the minimum number of crystals that Grisha should acquire in addition.

## 说明/提示

In the first sample case, Grisha needs five yellow and four blue crystals to create two yellow balls, one green ball, and one blue ball. To do that, Grisha needs to obtain two additional crystals: one yellow and one blue.

## 样例 #1

### 输入

```
4 3
2 1 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3 9
1 1 3

```

### 输出

```
1

```

## 样例 #3

### 输入

```
12345678 87654321
43043751 1000000000 53798715

```

### 输出

```
2147483648

```



---

---
title: "Jamie and Alarm Snooze"
layout: "post"
diff: 普及-
pid: CF916A
tag: ['进制', '概率论']
---

# Jamie and Alarm Snooze

## 题目描述

Jamie loves sleeping. One day, he decides that he needs to wake up at exactly $ hh:mm $ . However, he hates waking up, so he wants to make waking up less painful by setting the alarm at a lucky time. He will then press the snooze button every $ x $ minutes until $ hh:mm $ is reached, and only then he will wake up. He wants to know what is the smallest number of times he needs to press the snooze button.

A time is considered lucky if it contains a digit ' $ 7 $ '. For example, $ 13:07 $ and $ 17:27 $ are lucky, while $ 00:48 $ and $ 21:34 $ are not lucky.

Note that it is not necessary that the time set for the alarm and the wake-up time are on the same day. It is guaranteed that there is a lucky time Jamie can set so that he can wake at $ hh:mm $ .

Formally, find the smallest possible non-negative integer $ y $ such that the time representation of the time $ x·y $ minutes before $ hh:mm $ contains the digit ' $ 7 $ '.

Jamie uses 24-hours clock, so after $ 23:59 $ comes $ 00:00 $ .

## 输入格式

The first line contains a single integer $ x $ ( $ 1<=x<=60 $ ).

The second line contains two two-digit integers, $ hh $ and $ mm $ ( $ 00<=hh<=23,00<=mm<=59 $ ).

## 输出格式

Print the minimum number of times he needs to press the button.

## 说明/提示

In the first sample, Jamie needs to wake up at 11:23. So, he can set his alarm at 11:17. He would press the snooze button when the alarm rings at 11:17 and at 11:20.

In the second sample, Jamie can set his alarm at exactly at 01:07 which is lucky.

## 样例 #1

### 输入

```
3
11 23

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5
01 07

```

### 输出

```
0

```



---

---
title: "Messages"
layout: "post"
diff: 普及-
pid: CF964B
tag: ['贪心', '枚举', '概率论']
---

# Messages

## 题目描述

------------

Vasya有n封信。第i封信将在ti秒之后接收。 每封信都开始都值a元，但收到消息后，消息的成本每分钟减少B元(B可能变为负数)。Vasya可以在任意时刻接收到任何消息，也可在任意时刻读取它。读完消息后，Vasya的银行账户会收到该消息的当前成本。最初，Vasya的银行账户为0。 同时,每分钟Vasya的银行账户会收到C·k元,k是收到了但未读信的数量。 Vasya非常贪婪（又一个葛朗台），正因为如此，他想让所有的信息在T分钟后被阅读，使其利益最大化。


------------

## 输入格式

------------

第一行输入5个数 n , A , B , C 与 T
( 1<=n,A,B,C,T<=1000 ).
第二个字符串包含n个整数
ti
​ ( 1<=ti<=T ）


------------

## 输出格式

------------



------------

输出一个整数，问题的答案。

## 样例 #1

### 输入

```
4 5 5 3 5
1 5 5 4

```

### 输出

```
20

```

## 样例 #2

### 输入

```
5 3 1 1 3
2 2 2 1 1

```

### 输出

```
15

```

## 样例 #3

### 输入

```
5 5 3 4 5
1 2 3 4 5

```

### 输出

```
35

```



---

---
title: "Chess Placing"
layout: "post"
diff: 普及-
pid: CF985A
tag: ['排序', '费用流', '概率论']
---

# Chess Placing

## 题目描述

You are given a chessboard of size $ 1×n $ . It is guaranteed that  $ n $ is even. The chessboard is painted like this: "BWBW $ ... $ BW".

Some cells of the board are occupied by the chess pieces. Each cell contains no more than one chess piece. It is known that the total number of pieces equals to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/e98ace5c1ad627053f6404505602ba90672a171b.png).

In one step you can move one of the pieces one cell to the left or to the right. You cannot move pieces beyond the borders of the board. You also cannot move pieces to the cells that are already occupied.

Your task is to place all the pieces in the cells of the same color using the minimum number of moves (all the pieces must occupy only the black cells or only the white cells after all the moves are made).

## 输入格式

The first line of the input contains one integer $ n $ ( $ 2<=n<=100 $ ,  $ n $ is even) — the size of the chessboard.

The second line of the input contains ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/e98ace5c1ad627053f6404505602ba90672a171b.png) integer numbers ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/f69846f45d2fb290f17c0996035d8272d32fce7d.png) ( $ 1<=p_{i}<=n $ ) — initial positions of the pieces. It is guaranteed that all the positions are distinct.

## 输出格式

Print one integer — the minimum number of moves you have to make to place all the pieces in the cells of the same color.

## 说明/提示

In the first example the only possible strategy is to move the piece at the position $ 6 $ to the position $ 5 $ and move the piece at the position $ 2 $ to the position $ 3 $ . Notice that if you decide to place the pieces in the white cells the minimum number of moves will be $ 3 $ .

In the second example the possible strategy is to move ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/4f3653422b6429c3f89311497c438fd20547c4f8.png) in 4 moves, then ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/6c4181624e2b8f95750df668d534111d8ee2005d.png) in 3 moves, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/74a8630d5d683f941562dca49b5d40bcde2fe1ef.png) in 2 moves and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/b97ec32af1cd5347877d0d15bd3de6cc845fde76.png) in 1 move.

## 样例 #1

### 输入

```
6
1 2 6

```

### 输出

```
2

```

## 样例 #2

### 输入

```
10
1 2 3 4 5

```

### 输出

```
10

```



---

---
title: "Switches and Lamps"
layout: "post"
diff: 普及-
pid: CF985B
tag: ['枚举', '概率论']
---

# Switches and Lamps

## 题目描述

You are given $ n $ switches and $ m $ lamps. The $ i $ -th switch turns on some subset of the lamps. This information is given as the matrix $ a $ consisting of $ n $ rows and $ m $ columns where $ a_{i,j}=1 $ if the $ i $ -th switch turns on the $ j $ -th lamp and $ a_{i,j}=0 $ if the $ i $ -th switch is not connected to the $ j $ -th lamp.

Initially all $ m $ lamps are turned off.

Switches change state only from "off" to "on". It means that if you press two or more switches connected to the same lamp then the lamp will be turned on after any of this switches is pressed and will remain its state even if any switch connected to this lamp is pressed afterwards.

It is guaranteed that if you push all $ n $ switches then all $ m $ lamps will be turned on.

Your think that you have too many switches and you would like to ignore one of them.

Your task is to say if there exists such a switch that if you will ignore (not use) it but press all the other $ n-1 $ switches then all the $ m $ lamps will be turned on.

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ ( $ 1<=n,m<=2000 $ ) — the number of the switches and the number of the lamps.

The following $ n $ lines contain $ m $ characters each. The character $ a_{i,j} $ is equal to '1' if the $ i $ -th switch turns on the $ j $ -th lamp and '0' otherwise.

It is guaranteed that if you press all $ n $ switches all $ m $ lamps will be turned on.

## 输出格式

Print "YES" if there is a switch that if you will ignore it and press all the other $ n-1 $ switches then all $ m $ lamps will be turned on. Print "NO" if there is no such switch.

## 样例 #1

### 输入

```
4 5
10101
01000
00111
10000

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
4 5
10100
01000
00110
00101

```

### 输出

```
NO

```



---

