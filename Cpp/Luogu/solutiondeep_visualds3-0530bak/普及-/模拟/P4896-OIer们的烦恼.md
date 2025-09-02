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



**唯一算法分类**  
模拟

---

### **题解思路与算法要点**  
- **核心逻辑**：  
  1. **状态跟踪**：维护老师是否在场（`comes`变量）及每个学生的游戏状态（`play[j]`数组）。  
  2. **消息解析**：每条消息需完全匹配有效格式（如`XX started playing games!`），使用`strcmp`或字符串拼接严格验证。  
  3. **实时检查**：当老师在场时，立即扫描所有学生的游戏状态，标记违规者。  
  4. **字典序输出**：预先对学生名字排序，确保输出顺序正确。  

- **解决难点**：  
  - **输入处理**：消息可能含空格，需用`getline`或`gets`读取整行，再分离名字与动作。  
  - **有效消息判断**：严格匹配预定义模板（如通过`strcmp`或字符串拼接），过滤无效消息。  
  - **状态同步**：老师离开后需及时清除状态，避免误判。  

---

### **题解评分与推荐**  
1. **⑨baka（5星）**  
   - **亮点**：高效解析消息，分离名字与动作；利用`strcmp`精确匹配；预排序学生名字。  
   - **代码片段**：  
     ```cpp
     gets(s1); // 读取后缀动作
     if (!strcmp(s1, come)) comes = 1; // 严格匹配
     ```
   - **心得**：通过`cin`和`gets`组合处理空格，避免格式错误。

2. **Alarm5854（4星）**  
   - **亮点**：使用`set`自动管理排序和去重，简化逻辑。  
   - **代码片段**：  
     ```cpp
     set<string> catched; // 自动按字典序存储
     if (come.size()) catched.insert(*playing.begin());
     ```

3. **DEATH_ENDER（4星）**  
   - **亮点**：预处理所有有效消息模板，确保匹配准确性。  
   - **代码片段**：  
     ```cpp
     string qwq = b[j] + " started playing games!";
     if (qwq == s) playing[j] = true;
     ```

---

### **最优思路提炼**  
- **预排序**：输入学生名字后立即按字典序排序，避免后续处理。  
- **位掩码优化**（Tiphereth_A题解）：用`char`的二进制位表示状态，减少内存占用。  
- **实时标记**：在解析消息时立即更新状态，而非延迟处理。  

---

### **同类题目推荐**  
1. **P1055 ISBN号码**（字符串解析与验证）  
2. **P1308 统计单词数**（严格匹配与状态跟踪）  
3. **P1177 快速排序**（模拟与状态维护）  

---

### **可视化设计**  
- **像素动画**：  
  - **Canvas网格**：每个学生用像素块表示，绿色为正常，红色为被抓。  
  - **老师移动**：用8位风格的小人图标在网格边缘移动，进入时触发检查。  
- **音效**：  
  - **违规音效**：学生被抓时播放“哔”声，老师离开时播放“滴”声。  
- **自动演示**：  
  - **AI模式**：按时间步进处理消息，高亮当前操作的消息行。  

---

**核心代码片段（⑨baka题解）**  
```cpp
// 状态更新与检查
if (comes) {
    for (int j=1; j<=5; j++) {
        if (play[j] && !a[j]) { // 学生正在玩且未被标记
            a[j] = 1; // 标记为被抓
            len++;
        }
    }
}
// 输出处理
sort(stu+1, stu+6); // 预排序
for (int i=1; i<=5; i++) {
    if (a[i]) cout << stu[i] << " ";
}
```

---

**调试心得摘录**  
- **⑨baka**：`gets`读取后缀时需注意换行符，避免多读/少读。  
- **Alarm5854**：`set`的自动排序特性大幅简化输出逻辑，但需注意迭代器有效性。  
- **UnyieldingTrilobite**：字符串比较时发现`getline`与`char[]`性能差异，改用字符数组优化。  

通过以上分析与可视化设计，可清晰理解模拟过程及优化方向。

---
处理用时：83.20秒