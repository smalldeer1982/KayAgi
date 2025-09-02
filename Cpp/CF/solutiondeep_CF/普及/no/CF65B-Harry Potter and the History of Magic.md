# 题目信息

# Harry Potter and the History of Magic

## 题目描述

The History of Magic is perhaps the most boring subject in the Hogwarts school of Witchcraft and Wizardry. Harry Potter is usually asleep during history lessons, and his magical quill writes the lectures for him. Professor Binns, the history of magic teacher, lectures in such a boring and monotonous voice, that he has a soporific effect even on the quill. That's why the quill often makes mistakes, especially in dates.

So, at the end of the semester Professor Binns decided to collect the students' parchments with notes and check them. Ron Weasley is in a panic: Harry's notes may contain errors, but at least he has some notes, whereas Ron does not have any. Ronald also has been sleeping during the lectures and his quill had been eaten by his rat Scabbers. Hermione Granger refused to give Ron her notes, because, in her opinion, everyone should learn on their own. Therefore, Ron has no choice but to copy Harry's notes.

Due to the quill's errors Harry's dates are absolutely confused: the years of goblin rebellions and other important events for the wizarding world do not follow in order, and sometimes even dates from the future occur. Now Ron wants to change some of the digits while he copies the notes so that the dates were in the chronological (i.e. non-decreasing) order and so that the notes did not have any dates strictly later than $ 2011 $ , or strictly before than $ 1000 $ . To make the resulting sequence as close as possible to the one dictated by Professor Binns, Ron will change no more than one digit in each date into other digit. Help him do it.

## 样例 #1

### 输入

```
3
1875
1936
1721
```

### 输出

```
1835
1836
1921
```

## 样例 #2

### 输入

```
4
9999
2000
3000
3011
```

### 输出

```
1999
2000
2000
2011
```

## 样例 #3

### 输入

```
3
1999
5055
2000
```

### 输出

```
No solution
```

# AI分析结果



# 题目内容中文重写

## 题目描述

魔法史可能是霍格沃茨魔法学校最无聊的学科。哈利·波特在历史课上通常都在睡觉，他的魔法羽毛笔会替他记笔记。魔法史教授宾斯讲课如此单调乏味，连羽毛笔都会昏昏欲睡。因此羽毛笔经常出错，尤其在记录日期时。

学期末，宾斯教授决定检查学生们的羊皮纸笔记。罗恩·韦斯莱惊慌失措：哈利的笔记可能有错误，但至少他有笔记，而罗恩什么都没有。罗恩上课时也在睡觉，他的老鼠斑斑还咬坏了他的羽毛笔。赫敏·格兰杰拒绝借笔记给罗恩，因为她认为每个人都应该独立学习。因此罗恩只能抄哈利的笔记。

由于羽毛笔的错误，哈利记录的日期完全混乱：妖精叛乱等重要事件的年份没有按顺序排列，有时甚至出现未来的日期。现在罗恩想在抄写时修改某些数字，使得日期按时间顺序（非递减）排列，并且所有日期不严格晚于2011年，也不严格早于1000年。每个日期最多只能修改一个数字。帮助他完成这个任务。

# 算法分类
贪心

# 题解综合分析

## 思路共性
所有题解均采用贪心策略：对每个日期，在满足不小于前一个日期且位于[1000,2011]的前提下，修改为可能的最小值，以最大化后续日期的选择空间。

## 解法差异
1. **数据类型**：部分题解使用字符串处理，便于逐位修改和字典序比较；部分使用数值处理，需要拆解数位
2. **实现方式**：
   - 字符串派：暴力枚举每一位的0-9替换，取合法最小值
   - 数值派：拆解千/百/十/个位分别尝试修改
3. **边界处理**：字符串处理自动保留前导零，数值处理需注意千位不能为0

## 关键难点
1. 正确维护非递减序列的约束条件
2. 在允许单次修改的前提下，快速找到合法的最小值
3. 处理年份范围的边界条件（1000≤y≤2011）

# 精选题解

## 1. 作者：xiaoyuchenp（★★★★★）
**亮点**：
- 使用字符串处理，代码简洁易读
- 通过预置虚拟头节点（y[0]="1000"）统一处理逻辑
- 函数封装清晰，暴力枚举所有数位修改可能

**核心实现**：
```cpp
string returnmin(string a,string b){
    string ans="2012";
    for(int i=0;i<4;i++){
        for(int j=0;j<=9;j++){
            string tmp=b; tmp[i]=j+'0';
            if(tmp>=a) ans = min(tmp,ans);
        }
    }
    return ans;
}
// 主循环中逐个处理日期
```

## 2. 作者：LKY928261（★★★★☆）
**亮点**：
- 紧凑的代码结构，直接在主循环中处理
- 利用字符串的字典序比较特性
- 提前终止无效情况（k>"2011"）

**代码特点**：
```cpp
for(j=0;j<4;j++)for(g=0;g<=9;g++){
    t=a[i]; t[j]=g+48;
    if(t>=a[i-1]) k=min(k,t);
}
```

## 3. 作者：Lyrella（★★★★☆）
**亮点**：
- 预处理a[0]简化边界条件
- 双重循环枚举数位和数字
- 使用min函数直接比较字符串

**优化点**：
```cpp
string mi = "9999"; // 初始设为极大值
for(j=0;j<4;j++) for(k=0;k<10;k++){
    ch = a[i]; ch[j] = k+'0';
    if(ch >= a[i-1]) mi = min(ch, mi);
}
```

# 关键思路总结
1. **贪心顺序**：从前向后处理，每个日期取合法最小值
2. **字符串优势**：直接修改字符位、字典序比较简化实现
3. **边界处理**：
   - 虚拟头节点统一处理第一个日期的约束
   - 最终日期必须≤2011的全局检查
4. **暴力技巧**：四位数仅有4×10=40种修改可能，O(n)复杂度可接受

# 拓展练习
1. CF675B (Restoring Painting) - 类似约束条件下的数值构造
2. 洛谷P1102 (ISBN号码) - 字符串处理与校验位计算
3. 洛谷P1012 [拼数] - 贪心排序与字符串比较

---
处理用时：60.22秒