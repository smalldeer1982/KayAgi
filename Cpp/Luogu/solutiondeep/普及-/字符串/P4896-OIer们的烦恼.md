# 题目信息

# OIer们的烦恼

## 题目背景

OIer 们有一个烦恼，他们本来可以随心所欲玩游戏上网的，自从学校机房开启 URL 过滤后，OIer 们就开始在 luogu上 面找游戏玩。

但是他们刚玩 slay.one 几天之后 slay.one 就被封禁了，只有工作日的中午 2 小时可以嗨皮，并且会有帅气的老师来巡视机房，他们该怎么办呢？

## 题目描述

有 3 个帅气的老师 $A$，$B$ 和 $C$。

有 5 个学生 $a$，$b$，$c$，$d$，$e$。当他们当中的某一个人开始玩游戏时，会显示一条消息 `XX started playing games!`。当他们当中的某一个人停止玩游戏时，会显示一条消息 `XX stopped playing games!`。

当某个老师来巡视机房时，会显示一条消息：`XX came!`。如果某个老师走了，会显示一条消息：`XX left!`。

如果老师发现某个学生**正在**玩游戏时，请输出该学生的姓名。

## 说明/提示

对于 $20\%$ 的数据，$1\leq N\leq 23.3333333333333$          
对于 $30\%$ 的数据，$1\leq N\leq 999.999$，有一个点答案为 `How Good Oiers Are!`。         
对于 $60\%$ 的数据，$1\leq N\leq 100,000$。    
对于$99.9999999999999999999\%$的数据，不保证全部消息都符合题意。           
对于 $100\%$ 的数据，$1\leq N\leq 233,333$，数据有梯度。
 
### Tips:
1.消息中肯定有奇奇怪怪的东西  
2.消息必须**完全符合题意**才有效  
3.样例很恶心，数据很纯真   
4.数据满足不会同时有多个**老师**巡视。     
5.注意仔细阅读**题目**和**样例**，**该题有坑！**      

## 样例 #1

### 输入

```
10
A B C
a b c d e
A came!
a started playing games!
b started playing games!
A left!
c started playing games!
d started playing games!
e started playing games!
B came!
PS:zhe_ge_yang_li_hen_zheng_chang!
B left!```

### 输出

```
a b c d e
How Bad Oiers Are!```

## 样例 #2

### 输入

```
10
I_Love_You I_Hate_You Why_Not_love_Me
Gay Che_Wan_Dang QwQ WuMaRu PDD
I_Love_You came!
Gay:Why do you love me?
I_Love_You died!
I_Love_You left!
Che_Wan_Dang prepared to play Dong_Fang!
But nobody came!
QwQ:I am so QwQ,I love myself!
PDD started playing Gay!
Gay died!And WuMaRu cried!
WuMaRu:dai su ki!```

### 输出

```
How Good Oiers Are!```

## 样例 #3

### 输入

```
20
Sans QwQ QAQ
A B C D E
A started playing B!
B started fighting with A!
A won!
A get 10000000 Exp!
QwQ:I and QAQ are looking at you all!
C died!
D died!
E recovered 123456789 HP!
E started playing games!
Sans came!
Sans:It is really a nice day today!
Sans:The birds are singing!
Sans:The flowers in bloom!
Sans:In a beautiful day like this!
Sans:People like you!
Sans:Should burn in hell!
E tried to attack Sans!
Sans was killed!
Sans:Papyrus,do you want something?
E still played his Undertale!```

### 输出

```
E```

## 样例 #4

### 输入

```
20
a b c
A B C D E
A came!
a started playing games!
b came!
b came together!
b came! dan_shi_zhe_ju_hua_bu_dui!
A came came came!
b start playing games!
b left!
c came!
c left!
A left!
B started playing games!
A started playing game!
C started palying games!
E started playing games!
lu_ren_jia came!
lu_ren_jia:What are you doing?
C&D:We are studying!
lu_ren_jia:Good boy!
C:qwq```

### 输出

```
How Good Oiers Are!```

# AI分析结果

### 综合分析与结论

本题是一个典型的模拟题，核心在于处理字符串输入并判断老师和学生的状态变化。题解中大部分作者都采用了类似的思路：通过字符串匹配来判断老师和学生的行为，并根据老师的在场情况记录学生是否被抓到。主要的难点在于字符串的处理和状态的管理。

### 所选高星题解

#### 1. **作者：Alarm5854 (4星)**
- **关键亮点**：
  - 使用`set`数据结构自动处理重复和排序问题，简化了代码逻辑。
  - 通过`find`函数快速定位名字，避免了复杂的字符串处理。
  - 代码结构清晰，逻辑严谨，适合初学者学习。
- **个人心得**：
  - 作者提到调试时因为函数少加取地址符而浪费了20分钟，强调了细节的重要性。
- **核心代码**：
  ```cpp
  set<string> catched, playing, come;
  bool finds(string &name, string &s) {
      if(!s.find(A,0)) name=A, f=1;
      // 其他名字类似处理
      return f;
  }
  void check(string &name, string &s) {
      if(name==A||name==B||name==C) {
          if(s==name+" came!") come.insert(name);
          else if(s==name+" left!") come.erase(name);
      }
      // 学生处理类似
  }
  ```

#### 2. **作者：Tiphereth_A (4星)**
- **关键亮点**：
  - 使用位掩码（bitmask）来记录老师和学生的状态，极大地优化了空间和时间复杂度。
  - 通过宏定义简化了状态操作，代码简洁高效。
  - 位运算的使用展示了高级编程技巧，适合进阶学习。
- **核心代码**：
  ```cpp
  char onlineT, onlineS, deadS;
  #define _teacher_in(i)  onlineT|=1<<i
  #define _teacher_out(i) onlineT&=~(1<<i)
  #define _student_in(i)  onlineS|=1<<i
  #define _student_out(i) onlineS&=~(1<<i)
  #define _dead(i) deadS&(1<<i)
  #define _kill_student deadS|=onlineS
  ```

#### 3. **作者：yu__xuan (4星)**
- **关键亮点**：
  - 通过`getline`读取整行输入，避免了字符串分割的复杂性。
  - 使用`sort`函数对输出结果进行字典序排序，符合题目要求。
  - 代码结构清晰，注释详细，适合初学者理解。
- **核心代码**：
  ```cpp
  for(int i=1;i<=n;++i) {
      getline(std::cin,s);
      for(int j=1;j<=5;++j) {
          if(dead[j]) continue;
          std::string qwq=b[j]+" started playing games!";
          if(qwq==s) playing[j]=true;
          // 其他处理类似
      }
  }
  ```

### 最优关键思路与技巧

1. **数据结构选择**：使用`set`自动处理重复和排序，简化了代码逻辑。
2. **位掩码优化**：通过位运算记录状态，极大地优化了空间和时间复杂度。
3. **字符串处理**：通过`find`函数快速定位名字，避免了复杂的字符串处理。

### 可拓展之处

1. **类似题目**：可以扩展到更多状态管理的题目，如多线程同步问题、状态机设计等。
2. **位运算应用**：位掩码技巧可以应用于其他需要高效状态管理的场景，如棋盘问题、图论中的状态压缩等。

### 推荐洛谷题目

1. **P1003 铺地毯**（模拟题，考察状态管理）
2. **P1042 乒乓球**（字符串处理与状态管理）
3. **P1056 排座椅**（模拟题，考察状态管理与优化）

### 个人心得总结

- **调试经验**：细节决定成败，调试时要特别注意函数参数和返回值。
- **代码优化**：合理选择数据结构和算法可以大幅提升代码效率。
- **位运算技巧**：位掩码是处理状态管理问题的高效工具，值得深入学习。

---
处理用时：34.78秒