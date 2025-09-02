# 题目信息

# [USACO1.2] 命名那个数字 Name That Number

## 题目描述

在威斯康辛州牛守志大农场经营者之中，都习惯于请会计部门用连续数字给母牛打上烙印。但是,母牛本身并没感到这个系统的便利,它们更喜欢用它们喜欢的名字来呼叫它们的同伴，而不是用像这个的语句"C'mon, #4364, get along."。请写一个程序来帮助可怜的牧牛工将一只母牛的烙印编号翻译成一个可能的名字。因为母牛们现在都有手机了，使用标准的按键的排布来把将数目翻译为文字:( 除了 "Q" 和 "Z")

```
2: A,B,C     5: J,K,L    8: T,U,V
3: D,E,F     6: M,N,O    9: W,X,Y
4: G,H,I     7: P,R,S
```
可接受的名字都被放在这样一个叫作"dict.txt" 的文件中，它包含一连串的少于 5,000个（准确地说是4617个）可被接受的牛的名字。 (所有的名字都是大写的且已按字典序排列) 请读入母牛的编号并返回那些能从编号翻译出来并且在字典中的名字。举例来说,编号 4734 能产生的下列各项名字: GPDG GPDH GPDI GPEG GPEH GPEI GPFG GPFH GPFI GRDG GRDH GRDI GREG GREH GREI GRFG GRFH GRFI GSDG GSDH GSDI GSEG GSEH GSEI GSFG GSFH GSFI HPDG HPDH HPDI HPEG HPEH HPEI HPFG HPFH HPFI HRDG HRDH HRDI HREG HREH HREI HRFG HRFH HRFI HSDG HSDH HSDI HSEG HSEH HSEI HSFG HSFH HSFI IPDG IPDH IPDI IPEG IPEH IPEI IPFG IPFH IPFI IRDG IRDH IRDI IREG IREH IREI IRFG IRFH IRFI ISDG ISDH ISDI ISEG ISEH ISEI ISFG ISFH ISFI 碰巧，81个中只有一个"GREG"是有效的(在字典中)。

写一个程序来对给出的编号打印出所有的有效名字，如果没有则输出NONE。编号可能有12位数字。


## 样例 #1

### 输入

```
4734
NMSL
GREG
LSDC
....(太多了不写了)```

### 输出

```
GREG
```

# AI分析结果



### 综合分析与结论
本题核心在于建立字母与数字的映射关系，并高效匹配字典。各题解主要差异体现在预处理方式与匹配策略上，最优思路是将字母转换为数字建立快速查询结构，结合字典序特性进行剪枝或二分查找。

---

### 评分较高题解

#### 1. 作者：bjrjk (★★★★☆)
**关键亮点**  
- 预处理字母到数字的转换表，通过数组直接映射，时间复杂度O(1)  
- 利用字典已排序特性直接遍历匹配，代码简洁  
- 剪枝策略：长度不等直接跳过，减少无效比较  
**核心代码**  
```cpp
const char * str_trans = "2223334445556667 77888999";
for (char c : Dict[i]) 
    if (str_trans[c-'A'] != input[j]) break;
```
**个人心得**  
- 强调文件读取技巧："while(cin>>tmp)"自动处理EOF  
- 利用vector存储字典，避免内存溢出  

#### 2. 作者：Kewth (★★★★☆)  
**关键亮点**  
- 使用二维数组存储每个数字对应的字母表  
- 结合DFS生成所有可能组合，通过二分查找字典加速匹配  
- 按字典序输出结果，无需额外排序  
**核心代码**  
```cpp
char ft[10][4] = {/*字母表*/};
void dfs(int pos, string cur) {
    if(pos == len) {
        if(binary_search(dict, cur)) print(cur);
    }
    for(char c : ft[num[pos]]) dfs(pos+1, cur+c);
}
```

#### 3. 作者：zzqDeco (★★★★☆)  
**关键亮点**  
- 逆向思维：将字典中的名字预先转换为数字串  
- 构造结构体保存原始名与转换后数字串，直接比对输入  
- 预处理字典后查询复杂度降为O(N)  
**核心代码**  
```cpp
struct Node { string name, num; };
for (每个字典单词)
    q[i].num = 字母转数字后的字符串;
if (q[i].num == input) 输出q[i].name;
```

---

### 关键技术总结
1. **预处理映射表**  
   ```cpp
   const char trans[] = "2223334445556667777888999"; // A-Z对应数字
   ```
2. **逆向转换优化**  
   将字典中的名字预先转为数字串，避免对每个输入生成全部组合。
3. **剪枝策略**  
   比较前先判断长度，减少无效字符比对。
4. **二分查找加速**  
   利用字典已排序特性，对生成的名字进行二分查找。

---

### 拓展与同类题
**类似套路题**  
- **字符串转换**：P1024（电话号码字母组合）  
- **预处理优化**：P1177（快速排序+结构体预处理）  
- **字典序处理**：P1014（排序与二分查找结合）  

**举一反三**  
当遇到"大规模静态数据集匹配"问题时，可优先考虑数据集预处理为统一格式，再通过哈希或二分加速查询。

---

### 题解心得摘录
1. **bjrjk**：  
   > "字典元素少，直接遍历比生成所有组合更高效"  
   ——强调根据数据规模选择暴力或优化的平衡点  

2. **Kewth**：  
   > "试了19分才发现输入顺序是namenum.in在前"  
   ——提醒注意输入文件读取顺序的细节  

3. **zzqDeco**：  
   > "正着不行反着来"  
   ——逆向思维在优化中的典型应用，避免组合爆炸问题

---
处理用时：44.30秒