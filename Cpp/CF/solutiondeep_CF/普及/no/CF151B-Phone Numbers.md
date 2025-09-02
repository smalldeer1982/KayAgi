# 题目信息

# Phone Numbers

## 题目描述

Nvodsk 的冬天刺骨般的冷！于是一行 $n$ 个朋友们会坐出租车，点一个披萨，然后给女生打电话。这个城市中的电话由三组数字组成（如 12-34-56）。每个朋友都有一本大小为 $s_{i}$（此为电话号码的数量）的电话簿。出租车司机的电话号由六个相同的数字构成（如 22-22-22），披萨外卖的电话则由六个递减的数字构成（如 98-73-21），剩下的号码都是女生的电话。

现在你朋友的电话簿都交到了你手里。计算一下当你想做某件事时最好去找谁（有着最多相应类型的电话号码的人）。

如果一个人的电话簿中同一个电话号码出现了两次，你也需要计数两次。也就是说，你需要考虑每个号码出现在电话簿中的次数。

## 说明/提示

第一个样例中有四个朋友。Fedorov 的电话簿包含一个出租车司机的电话号码和一个披萨外卖的电话号码，Melnikov 的电话簿只有 $3$ 个女孩的电话号码，而Rogulenko 的电话簿则有 $6$ 个出租车司机的电话号码和一个披萨外卖的电话号码，Kaluzhin 的电话簿有 $2$ 个出租车司机的电话号码和一个披萨外卖的电话号码。

因此，如果你想要打出租车，显然你应该给 Rogulenko 打电话，如果你想要定个披萨，你可以给 Rogulenko、Fedorov、Kaluzhin 中的任何一个打电话（他们每个人都只有一个电话号码）。Melnikov 则有最多的女生的电话号码。

## 样例 #1

### 输入

```
4
2 Fedorov
22-22-22
98-76-54
3 Melnikov
75-19-09
23-45-67
99-99-98
7 Rogulenko
22-22-22
11-11-11
33-33-33
44-44-44
55-55-55
66-66-66
95-43-21
3 Kaluzhin
11-11-11
99-99-99
98-65-32
```

### 输出

```
If you want to call a taxi, you should call: Rogulenko.
If you want to order a pizza, you should call: Fedorov, Rogulenko, Kaluzhin.
If you want to go to a cafe with a wonderful girl, you should call: Melnikov.
```

## 样例 #2

### 输入

```
3
5 Gleb
66-66-66
55-55-55
01-01-01
65-43-21
12-34-56
3 Serega
55-55-55
87-65-43
65-55-21
5 Melnik
12-42-12
87-73-01
36-04-12
88-12-22
82-11-43
```

### 输出

```
If you want to call a taxi, you should call: Gleb.
If you want to order a pizza, you should call: Gleb, Serega.
If you want to go to a cafe with a wonderful girl, you should call: Melnik.
```

## 样例 #3

### 输入

```
3
3 Kulczynski
22-22-22
65-43-21
98-12-00
4 Pachocki
11-11-11
11-11-11
11-11-11
98-76-54
0 Smietanka
```

### 输出

```
If you want to call a taxi, you should call: Pachocki.
If you want to order a pizza, you should call: Kulczynski, Pachocki.
If you want to go to a cafe with a wonderful girl, you should call: Kulczynski.
```

# AI分析结果



### 中文题目重写

# 电话号码

## 题目描述

Nvodsk 的冬天寒冷刺骨！一行 $n$ 个朋友打算坐出租车、点披萨并给女生打电话。城市中的电话号码格式为三组两位数字（如 12-34-56）。每个朋友有一个包含 $s_i$ 个电话号码的通讯录。出租车司机的号码由六个相同数字组成（如 22-22-22），披萨店的号码由六个递减数字组成（如 98-73-21），其余号码为女生号码。

你的任务是：根据朋友们的通讯录，找出在需要特定服务时应该联系的人（对应类型号码最多的人）。若同一号码多次出现，需重复计数。

## 说明/提示

样例 1 中，Fedorov 的通讯录包含一个出租车号码和一个披萨号码，Melnikov 有 3 个女生号码，Rogulenko 有 6 个出租车号码和一个披萨号码，Kaluzhin 有 2 个出租车号码和一个披萨号码。因此，当需要出租车时应联系 Rogulenko，披萨服务可联系 Fedorov、Rogulenko 或 Kaluzhin，女生号码最多的是 Melnikov。

---

### 算法分类
**模拟**

---

### 题解分析与结论

#### 核心思路
1. **号码分类**：将每个号码分解为六个独立字符，直接比较数字特征：
   - 出租车：所有字符相同
   - 披萨：严格递减序列
   - 其他归为女生号码
2. **数据存储**：使用结构体记录每个人的三类号码计数
3. **极值统计**：两次遍历，第一次确定最大值，第二次收集所有符合条件的人名
4. **输出控制**：通过标记变量或动态数组处理逗号分隔格式

#### 关键技巧
- **字符串逐位处理**：避免将号码分段转换为整数，直接按字符处理确保准确性
- **顺序保留**：严格按输入顺序遍历，确保并列情况按首次出现顺序输出
- **格式标记法**：使用布尔标记控制逗号输出，简化格式处理

---

### 精选题解

#### 题解 1 - FQR_（5⭐）
**亮点**：
- 字符级精确判断
- 输入输出格式处理规范
- 代码结构清晰易扩展

**核心代码**：
```cpp
struct s { string name; int a,b,c; } a[105];

// 号码类型判断
char b[10];
cin >> b[0] >> b[1] >> ch >> b[2] >> b[3] >> ch >> b[4] >> b[5];
if(b[0]==b[1] && ... && b[4]==b[5]) a[k].a++; // 出租车
else if(b[0]>b[1] && b[1]>b[2] && ... && b[4]>b[5]) a[k].b++; // 披萨
else a[k].c++; // 女生

// 输出控制
bool aaa=1;
for(int i=0;i<n;i++) {
    if(a[i].a == maxa) {
        if(aaa) cout << a[i].name, aaa=0;
        else cout << ", " << a[i].name;
    }
}
```

#### 题解 2 - 松鼠的星星（5⭐）
**亮点**：
- 独立判断函数提升可读性
- 动态数组存储结果
- 模块化输出处理

**核心代码**：
```cpp
bool isTaxi(string s) {
    for(int i=1; i<s.length(); i++) 
        if(s[i]!=s[0] && s[i]!='-') return false;
    return true;
}

vector<string> ans;
for(int i=0; i<n; i++) {
    if(cnt[i] == max_cnt) 
        ans.push_back(name[i]);
}

// 输出时处理逗号
for(int i=0; i<ans.size(); i++) {
    if(i != 0) cout << ", ";
    cout << ans[i];
}
```

#### 题解 3 - songtaoran（4⭐）
**亮点**：
- 紧凑型条件判断
- 即时最大值更新
- 字符串直接操作

**核心代码**：
```cpp
for(int j=1; j<=s; j++) {
    string num;
    cin >> num;
    if(num[0]==num[1] && ... ) taxi++;
    else if(num[0]>num[1] && ... ) pizza++;
    else girl++;
}

// 动态维护最大值和结果集
if(taxi > current_max) {
    result.clear();
    result.push_back(name);
}
```

---

### 拓展练习
1. **P1051** 谁拿了最多奖学金（复杂条件统计）
2. **P1308** 统计单词数（字符串模式匹配）
3. **P1598** 垂直柱状图（频率统计与格式化输出）

---

### 总结心得
- **调试经验**：必须验证披萨号码的严格递减条件，曾因误判连续两位数导致 WA
- **优化意识**：避免重复遍历，两次独立遍历（统计极值+收集结果）更清晰
- **格式教训**：输出末尾句号易遗漏，建议先构建完整字符串再统一输出

掌握字符串特征提取和结构化数据处理是解决此类模拟题的关键，注意边界条件和输出细节可大幅减少调试时间。

---
处理用时：280.92秒