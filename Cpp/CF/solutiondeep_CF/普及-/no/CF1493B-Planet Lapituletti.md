# 题目信息

# Planet Lapituletti

## 题目描述

The time on the planet Lapituletti goes the same way it goes on Earth but a day lasts $ h $ hours and each hour lasts $ m $ minutes. The inhabitants of that planet use digital clocks similar to earth ones. Clocks display time in a format HH:MM (the number of hours in decimal is displayed first, then (after the colon) follows the number of minutes in decimal; the number of minutes and hours is written with leading zeros if needed to form a two-digit number). Hours are numbered from $ 0 $ to $ h-1 $ and minutes are numbered from $ 0 $ to $ m-1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1493B/60f2fad68c8c57b27eed490aaadafcab0fd86b23.png)That's how the digits are displayed on the clock. Please note that digit $ 1 $ is placed in the middle of its position.

A standard mirror is in use on the planet Lapituletti. Inhabitants often look at the reflection of the digital clocks in the mirror and feel happy when what you see on the reflected clocks is a valid time (that means that you see valid digits in the reflection and this time can be seen on the normal clocks at some moment of a day).

The image of the clocks in the mirror is reflected against a vertical axis.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1493B/45e02f44df121c5701b96d2a2728d34df90fea6a.png)The reflection is not a valid time.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1493B/a42f523b339fb6fa2f4820a2d60d05f67a7624be.png)

The reflection is a valid time with $ h=24 $ , $ m = 60 $ . However, for example, if $ h=10 $ , $ m=60 $ , then the reflection is not a valid time.

An inhabitant of the planet Lapituletti begins to look at a mirrored image of the clocks at some time moment $ s $ and wants to know the nearest future time moment (which can possibly happen on the next day), when the reflected clock time is valid.

It can be shown that with any $ h $ , $ m $ , $ s $ such a moment exists. If the reflected time is correct at the moment the inhabitant began to look at the clock, that moment is considered the nearest.

You are asked to solve the problem for several test cases.

## 说明/提示

In the second test case it is not hard to show that the reflection of 23:59 is incorrect, while the reflection of the moment 00:00 on the next day is correct.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1493B/50d79fafef9eb95bbfe6fa29f77ca1c6567a1615.png)

## 样例 #1

### 输入

```
5
24 60
12:21
24 60
23:59
90 80
52:26
1 100
00:01
10 10
04:04```

### 输出

```
12:21
00:00
52:28
00:00
00:00```

# AI分析结果

### 题目内容
# Planet Lapituletti

## 题目描述
在拉皮图莱蒂星球上，时间的流逝方式与地球相同，但一天有 $h$ 小时，每小时有 $m$ 分钟。该星球的居民使用类似于地球的数字时钟。时钟以 HH:MM 的格式显示时间（首先以十进制显示小时数，然后（在冒号之后）以十进制显示分钟数；如果需要形成两位数，则小时数和分钟数会添加前导零）。小时数从 $0$ 到 $h - 1$ 编号，分钟数从 $0$ 到 $m - 1$ 编号。

![数字在时钟上的显示方式](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1493B/60f2fad68c8c57b27eed490aaadafcab0fd86b23.png)这就是数字在时钟上的显示方式。请注意，数字 $1$ 位于其位置的中间。

在拉皮图莱蒂星球上使用标准镜子。居民们经常看数字时钟在镜子中的反射，当看到反射时钟上的时间是有效时间（这意味着在反射中看到的是有效数字，并且这个时间在正常时钟的某一时刻可以看到）时，他们会感到高兴。

时钟在镜子中的图像是沿垂直轴反射的。

![反射不是有效时间](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1493B/45e02f44df121c5701b96d2a2728d34df90fea6a.png)反射不是有效时间。

![反射是有效时间，h = 24，m = 60](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1493B/a42f523b339fb6fa2f4820a2d60d05f67a7624be.png)反射是有效时间，其中 $h = 24$，$m = 60$。然而，例如，如果 $h = 10$，$m = 60$，那么反射就不是有效时间。

拉皮图莱蒂星球的一位居民在某个时刻 $s$ 开始看镜子中的时钟图像，并想知道最近的未来时刻（可能发生在第二天），此时反射的时钟时间是有效的。

可以证明，对于任何 $h$，$m$，$s$，这样的时刻都存在。如果居民开始看时钟的时刻反射时间是正确的，那么该时刻被认为是最近的时刻。

你需要为几个测试用例解决这个问题。

## 说明/提示
在第二个测试用例中，不难证明 23:59 的反射是不正确的，而第二天 00:00 的反射是正确的。

![说明图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1493B/50d79fafef9eb95bbfe6fa29f77ca1c6567a1615.png)

## 样例 #1
### 输入
```
5
24 60
12:21
24 60
23:59
90 80
52:26
1 100
00:01
10 10
04:04
```
### 输出
```
12:21
00:00
52:28
00:00
00:00
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是通过枚举来寻找满足条件的时间。主要差异在于枚举的方式和判断时间合法性的具体实现细节。各题解都利用了数字翻转的特性，通过建立数字翻转映射数组来辅助判断。难点在于处理时间进位、前导零输出以及准确判断翻转后时间的合法性。

### 所选的题解
- **作者：LinkZelda（3星）**
    - **关键亮点**：直接枚举经过的时间，通过函数 `check` 判断时间合法性，逻辑较为清晰，对时间进位和合法性判断有较为详细的实现。
    - **重点代码核心思想**：`check` 函数中，根据经过时间计算新的小时和分钟，处理进位后，通过映射数组 `to` 计算翻转后的时间，判断其是否在合法范围内。
    ```cpp
    bool check(int nowh, int nowm, int k) {
        int hh = k / m;
        int nh = nowh + hh;
        k -= hh * m;
        int mm = k;
        int nm = nowm + mm;
        if (nm > m - 1) {
            nh++;
            nm -= m;
        }
        if (nh > h - 1) {
            printf("00:00\n");
            return true;
        }
        int ansh = 0, ansm = 0;
        int reth = nh, retm = nm;
        if (nm < 10)
            ansh = to[nm % 10] * 10;
        else while (nm) {
            ansh = ansh * 10 + to[nm % 10];
            nm /= 10;
        }
        if (nh < 10)
            ansm = to[nh % 10] * 10;
        else while (nh) {
            ansm = ansm * 10 + to[nh % 10];
            nh /= 10;
        }
        if (0 <= ansm && ansm <= m - 1 && 0 <= ansh && ansh <= h - 1) {
            if (reth < 10) {
                printf("0%d:", reth);
            } else
                printf("%d:", reth);
            if (retm < 10) {
                printf("0%d\n", retm);
            } else
                printf("%d\n", retm);
            return true;
        }
        return false;
    }
    ```
- **作者：Iron_Heart（3星）**
    - **关键亮点**：从给定时间开始枚举，通过字符串操作实现数字翻转和合法性判断，代码简洁明了。
    - **重点代码核心思想**：`ok` 函数中，将小时和分钟转为字符串，添加前导零后，对每一位进行翻转，反转字符串后再转为数字，判断是否在合法范围。
    ```cpp
    bool ok(int ho, int mi) {
        string sh = to_string(ho);
        string sm = to_string(mi);
        if (sh.size() == 1) {
            sh = "0" + sh;
        }
        if (sm.size() == 1) {
            sm = "0" + sm;
        }
        for (int i = 0; i < sh.size(); ++i) {
            if (refl[sh[i] - '0'] == -1) {
                return 0;
            }
            sh[i] = '0' + refl[sh[i] - '0'];
        }
        for (int i = 0; i < sm.size(); ++i) {
            if (refl[sm[i] - '0'] == -1) {
                return 0;
            }
            sm[i] = '0' + refl[sm[i] - '0'];
        }
        reverse(sm.begin(), sm.end());
        reverse(sh.begin(), sh.end());
        stringstream sa(sm), sb(sh);
        sa >> ho;
        sb >> mi;
        return ho < h && mi < m;
    }
    ```
- **作者：冰糖鸽子（3星）**
    - **关键亮点**：代码结构清晰，通过定义 `check` 和 `gonext` 函数分别负责合法性判断和时间推进，逻辑明确。
    - **重点代码核心思想**：`check` 函数判断当前时间数字能否合法翻转并计算翻转后的时间，判断是否在范围内；`gonext` 函数负责推进时间。
    ```cpp
    bool check() {
        if (To[H / 10] == -1 || To[H % 10] == -1 || To[M / 10] == -1 || To[M % 10] == -1) {
            return 0;
        }
        NM = 10 * To[H % 10] + To[H / 10];
        NH = 10 * To[M % 10] + To[M / 10];
        if (NH < h && NM < m) return 1;
        return 0;
    }
    bool gonext() {
        M++;
        if (M == m) { H++; M = 0; }
        if (H == h) { H = 0; }
        return 1;
    }
    ```

### 最优关键思路或技巧
通过建立数字翻转映射数组，利用枚举法从给定时间开始向后枚举所有可能时间，逐一判断其合法性。在实现过程中，合理处理时间进位、前导零输出以及数字翻转后的合法性判断等细节。

### 可拓展之处
同类型题通常围绕时间、图形等具有对称或翻转特性的场景，通过枚举结合特定规则判断来求解。类似算法套路是先明确枚举范围，再建立规则判断函数，在枚举过程中应用该函数筛选出符合条件的结果。

### 洛谷题目推荐
 - [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举不同数字组合来解决问题，与本题枚举思路类似。
 - [P1157 组合的输出](https://www.luogu.com.cn/problem/P1157)：考察枚举组合情况，锻炼对枚举过程的控制和处理能力。
 - [P1469 找筷子](https://www.luogu.com.cn/problem/P1469)：虽然有更优解法，但也可通过枚举尝试解决，与本题枚举判断合法性有相似之处。

### 个人心得摘录与总结
无。 

---
处理用时：117.12秒