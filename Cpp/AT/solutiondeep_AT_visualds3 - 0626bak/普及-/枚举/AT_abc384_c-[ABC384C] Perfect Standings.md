# 题目信息

# [ABC384C] Perfect Standings

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc384/tasks/abc384_c

高橋くんは、プログラミングコンテストを主催することにしました。

コンテストは A 問題、B 問題、C 問題、D 問題、E 問題の $ 5 $ 問からなり、それぞれの配点は $ a $ 点、$ b $ 点、$ c $ 点、$ d $ 点、$ e $ 点です。

コンテストには $ 31 $ 人が参加し、全員が $ 1 $ 問以上解きました。

より具体的には、文字列 `ABCDE` の空でない（連続するとは限らない）部分列すべてについて、その部分列を名前とする参加者が存在し、その参加者は名前に含まれる文字に対応する問題をすべて解き、それ以外の問題は解きませんでした。

例えば、A さんは A 問題のみを、BCE さんは B 問題、C 問題、E 問題を解きました。

参加者の名前を、取った点数が大きいほうから順に出力してください。 ただし、参加者が取った点数は、その参加者が解いた問題の配点の合計です。

ただし、同じ点数を獲得した参加者については、名前が辞書順で小さいほうを先に出力してください。

 辞書順で小さいとは？辞書順とは、一言で説明すると「単語が辞書に載っている順番」を意味します。

より厳密には、英大文字からなる相異なる文字列 $ S,T $ について、$ S $ が $ T $ より辞書順で小さいとは、以下の条件のどちらかが成り立つことを意味します。

- $ S $ の長さ $ |S| $ が $ T $ の長さより短く、$ T $ の先頭 $ |S| $ 文字が $ S $ と一致する
- ある整数 $ 1\leq\ i\leq\min\lbrace|S|,|T|\rbrace $ が存在して、次の $ 2 $ つの条件を両方を満たす
  - $ 1\leq\ j\lt\ i $ を満たすすべての整数 $ j $ に対して $ S $ の $ j $ 文字目と $ T $ の $ j $ 文字目が等しい
  - $ S $ の $ i $ 文字目が $ T $ の $ i $ 文字目よりアルファベット順で小さい
 
例えば、$ S= $ `AB` $ ,T= $ `ABC` とすると、ひとつめの条件が成り立つため $ S $ は $ T $ より小さいです。 また、$ S= $ `ABD` $ ,T= $ `ACD` とすると、ふたつめの条件が $ i=2 $ で成り立つため $ S $ は $ T $ より小さいです。

## 说明/提示

### 制約

- $ 100\leq\ a\leq\ b\leq\ c\leq\ d\leq\ e\leq\ 2718 $
- 入力はすべて整数
 
### Sample Explanation 1

それぞれの参加者の得点は以下のようになります。 !\[\](https://img.atcoder.jp/abc384/4dac80dfad9b0f66c75fec40eedb5e2d.png) 例えば、ADE さんと BCE さんは同じ得点を獲得していますが、ADE さんのほうが辞書順で小さい名前をもつため、ADE さんを先に出力してください。

## 样例 #1

### 输入

```
400 500 600 700 800```

### 输出

```
ABCDE

BCDE

ACDE

ABDE

ABCE

ABCD

CDE

BDE

ADE

BCE

ACE

BCD

ABE

ACD

ABD

ABC

DE

CE

BE

CD

AE

BD

AD

BC

AC

AB

E

D

C

B

A```

## 样例 #2

### 输入

```
800 800 900 900 1000```

### 输出

```
ABCDE

ACDE

BCDE

ABCE

ABDE

ABCD

CDE

ACE

ADE

BCE

BDE

ABE

ACD

BCD

ABC

ABD

CE

DE

AE

BE

CD

AC

AD

BC

BD

AB

E

C

D

A

B```

## 样例 #3

### 输入

```
128 256 512 1024 2048```

### 输出

```
ABCDE

BCDE

ACDE

CDE

ABDE

BDE

ADE

DE

ABCE

BCE

ACE

CE

ABE

BE

AE

E

ABCD

BCD

ACD

CD

ABD

BD

AD

D

ABC

BC

AC

C

AB

B

A```

# AI分析结果



## 唯一算法分类
无算法分类

## 综合分析与结论
题目要求将 31 名参赛者按得分降序、字典序升序排列。核心难点在于生成所有合法子序列，并正确处理排序规则。所有题解均采用暴力枚举思路，差异主要体现在子序列生成方式和数据结构选择。

### 核心算法流程
1. **子集生成**：通过位运算或循环枚举所有非空子集，按原字符串顺序生成合法名字（字符顺序递增）
2. **分数计算**：根据选中题目对应的分数累加
3. **双关键字排序**：优先按分数降序，同分时按字典序升序

### 可视化设计思路
![像素动画示例](https://img.poki.com/cdn-cgi/image/quality=78,width=600,height=600,fit=cover,f=auto/2d3c8d9c3dfa2cde2c0c9d0f9c2a5b6d.gif)  
- **Canvas 网格**：每个方块代表一个参赛者，显示名字和分数，颜色深浅表示分数高低
- **位运算过程**：用像素高亮展示二进制位选中状态（如红色像素表示选中对应题目）
- **排序动画**：通过方块位置交换演示排序过程，字典序比较时显示字符对比光效
- **音效设计**：二进制位切换时触发电子音，排序完成时播放8-bit胜利音效

## 题解清单 (≥4星)

### 1. 4041nofoundGeoge（5星）
**关键亮点**：  
- 位运算生成所有子集，代码简洁高效  
- 自动处理名字顺序，无需手动维护列表  
- 使用 map 分组分数，天然支持多级排序  

### 2. jinhangdong（4星）
**关键亮点**：  
- 五层循环暴力枚举，逻辑直观易懂  
- 通过字符串拼接自动处理字典序  
- 代码结构清晰，适合初学者理解  

### 3. ryf2011（4星） 
**关键亮点**：  
- 打表预处理名字列表，避免生成逻辑  
- 显式字符遍历计算分数，便于调试  
- 注释详细，可读性较强  

## 最优思路提炼
**位运算+预排序技巧**：  
1. 用 `1<<n` 位掩码表示题目选择状态  
2. 按原字符串顺序生成名字（保证子序列合法性）  
3. 使用 `map<int, vector<string>>` 分组存储同分名字  
4. 每组内部单独排序处理字典序  

```cpp
// 关键代码片段
for(int i = 1; i < (1<<5); ++i){
    string name;
    int score = 0;
    for(int j=0; j<5; j++){  // 按ABCDE顺序处理位
        if(i & (1<<j)){
            name += 'A'+j;
            score += scores[j];
        }
    }
    mp[score].push_back(name);
}
// 最终输出时逆序遍历map键
```

## 同类题目推荐
1. **洛谷P1036** - 子集和问题  
2. **LeetCode 78. Subsets** - 生成所有子集  
3. **Atcoder ABC353C** - 双重条件排序  

## 个人心得摘录
> "调试时发现名字顺序错误，意识到子序列必须保持原字符串顺序。改用位运算顺序处理位后问题解决" —— 4041nofoundGeoge

## 可视化实现
```html
<!-- 核心动画逻辑片段 -->
<canvas id="demo" width="800" height="600"></canvas>
<script>
const questions = ['A','B','C','D','E'];
function drawEntry(ctx, x, y, name, score) {
    ctx.fillStyle = `hsl(${200-score*2},70%,60%)`;
    ctx.fillRect(x, y, 120, 40);
    ctx.fillStyle = "#FFF";
    ctx.font = "12px 'Press Start 2P'";
    ctx.fillText(name, x+10, y+25);
}
function animateSort(entries) {
    let step = 0;
    const animation = setInterval(() => {
        if(compare(entries[step], entries[step+1])) {
            [entries[step], entries[step+1]] = [entries[step+1], entries[step]];
            playSwapSound();  // 播放交换音效
        }
        redrawCanvas(entries);
        if(++step >= entries.length-1) clearInterval(animation);
    }, 500);
}
</script>
```

---
处理用时：186.89秒