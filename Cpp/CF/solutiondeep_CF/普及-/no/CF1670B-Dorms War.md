# 题目信息

# Dorms War

## 题目描述

Hosssam decided to sneak into Hemose's room while he is sleeping and change his laptop's password. He already knows the password, which is a string $ s $ of length $ n $ . He also knows that there are $ k $ special letters of the alphabet: $ c_1,c_2,\ldots, c_k $ .

Hosssam made a program that can do the following.

1. The program considers the current password $ s $ of some length $ m $ .
2. Then it finds all positions $ i $ ( $ 1\le i<m $ ) such that $ s_{i+1} $ is one of the $ k $ special letters.
3. Then it deletes all of those positions from the password $ s $ even if $ s_{i} $ is a special character. If there are no positions to delete, then the program displays an error message which has a very loud sound.

For example, suppose the string $ s $ is "abcdef" and the special characters are 'b' and 'd'. If he runs the program once, the positions $ 1 $ and $ 3 $ will be deleted as they come before special characters, so the password becomes "bdef". If he runs the program again, it deletes position $ 1 $ , and the password becomes "def". If he is wise, he won't run it a third time.

Hosssam wants to know how many times he can run the program on Hemose's laptop without waking him up from the sound of the error message. Can you help him?

## 说明/提示

In the first test case, the program can run $ 5 $ times as follows: $ \text{iloveslim} \to \text{ilovslim} \to \text{iloslim} \to \text{ilslim} \to \text{islim} \to \text{slim} $

In the second test case, the program can run $ 2 $ times as follows: $ \text{joobeel} \to \text{oel} \to \text{el} $

In the third test case, the program can run $ 3 $ times as follows: $ \text{basiozi} \to \text{bioi} \to \text{ii} \to \text{i} $ .

In the fourth test case, the program can run $ 5 $ times as follows: $ \text{khater} \to \text{khatr} \to \text{khar} \to \text{khr} \to \text{kr} \to \text{r} $

In the fifth test case, the program can run only once as follows: $ \text{abobeih} \to \text{h} $

In the sixth test case, the program cannot run as none of the characters in the password is a special character.

## 样例 #1

### 输入

```
10
9
iloveslim
1 s
7
joobeel
2 o e
7
basiozi
2 s i
6
khater
1 r
7
abobeih
6 a b e h i o
5
zondl
5 a b c e f
6
shoman
2 a h
7
shetwey
2 h y
5
samez
1 m
6
mouraz
1 m```

### 输出

```
5
2
3
5
1
0
3
5
2
0```

# AI分析结果

### 题目内容
# Dorms War

## 题目描述
Hosssam决定趁Hemose睡觉时潜入他的房间，更改他笔记本电脑的密码。他已经知道密码，是一个长度为n的字符串s。他还知道字母表中有k个特殊字母：$c_1,c_2,\ldots, c_k$ 。

Hosssam编写了一个程序，该程序可以执行以下操作：
1. 程序考虑当前长度为m的密码s。
2. 然后找到所有满足$1\le i<m$且$s_{i + 1}$是k个特殊字母之一的位置i。
3. 然后从密码s中删除所有这些位置，即使$s_{i}$是特殊字符。如果没有要删除的位置，则程序会显示一条错误消息，该消息会发出很大的声音。

例如，假设字符串s是“abcdef”，特殊字符是'b'和'd'。如果他运行程序一次，位置1和3将被删除，因为它们在特殊字符之前，所以密码变为“bdef”。如果他再次运行程序，它会删除位置1，密码变为“def”。如果他明智的话，就不会再运行第三次。

Hosssam想知道他可以在不吵醒Hemose的情况下在他的笔记本电脑上运行该程序多少次。你能帮他吗？

## 说明/提示
在第一个测试用例中，程序可以运行5次，如下所示：$\text{iloveslim} \to \text{ilovslim} \to \text{iloslim} \to \text{ilslim} \to \text{islim} \to \text{slim}$ 

在第二个测试用例中，程序可以运行2次，如下所示：$\text{joobeel} \to \text{oel} \to \text{el}$ 

在第三个测试用例中，程序可以运行3次，如下所示：$\text{basiozi} \to \text{bioi} \to \text{ii} \to \text{i}$ 。

在第四个测试用例中，程序可以运行5次，如下所示：$\text{khater} \to \text{khatr} \to \text{khar} \to \text{khr} \to \text{kr} \to \text{r}$ 

在第五个测试用例中，程序只能运行一次，如下所示：$\text{abobeih} \to \text{h}$ 

在第六个测试用例中，程序无法运行，因为密码中没有一个字符是特殊字符。

## 样例 #1
### 输入
```
10
9
iloveslim
1 s
7
joobeel
2 o e
7
basiozi
2 s i
6
khater
1 r
7
abobeih
6 a b e h i o
5
zondl
5 a b c e f
6
shoman
2 a h
7
shetwey
2 h y
5
samez
1 m
6
mouraz
1 m
```
### 输出
```
5
2
3
5
1
0
3
5
2
0
```

### 算法分类
贪心

### 综合分析与结论
所有题解思路基本一致，均发现最大操作次数等于两个特殊字符间的最长距离（中间无其他特殊字符）。算法要点在于遍历字符串，标记特殊字符，记录相邻特殊字符的位置并计算距离，取最大距离作为结果。解决难点主要是理解题目中操作与报错的定义，将其转化为求特殊字符间距离的问题。

### 所选的题解
- **作者：Withershine (5星)**
  - **关键亮点**：思路清晰，对操作次数等于特殊字符最长距离的解释详细，代码有读入优化以避免超时。
  - **个人心得**：吐槽直接读入k个字符会超时，在读入k时加了小优化，将后面空格符也读入，在此处被卡很久。
  - **核心代码**：
```cpp
ll T, n, k;
char s[100005], ch;
ll t[27], last, max_dis;
signed main()
{
    T = read();
    while(T--)
    {
        max_dis = 0;
        fr(i, 0, 26)
        {
            t[i] = 0;
        }
        n = read();
        scanf("%s", s + 1);
        k = read();
        fr(i, 1, k)
        {
            scanf("%c", &ch);
            getchar();
            t[ch - 'a'] = 1;
        }
        last = 1;
        fr(i, 1, n)
        {
            if(t[s[i] - 'a'])
            {
                max_dis = max(max_dis, i - last);
                last = i;
            }
        }
        printf("%lld\n", max_dis);
    }
    system("pause");
	return 0;
}
```
  - **核心实现思想**：通过read函数快速读入数据，用数组t标记特殊字符，遍历字符串s，当遇到特殊字符时，计算其与上一个特殊字符的距离并更新max_dis，最后输出max_dis。

- **作者：ssSSSss_sunhaojia (4星)**
  - **关键亮点**：对报错定义理解清晰，表述准确，代码简洁明了。
  - **核心代码**：
```cpp
LL T, n, k, lst, ans, f[220]; 
char s[110000], ch;  
int main() {
    IOS;
    cin >> T; 
    while(T --) {
        cin >> n >> s + 1;
        cin >> k; 
        for(re char i = 'a'; i <= 'z'; i ++) f[i] = 0; 
        for(re int i = 1; i <= k; i ++) cin >> ch, f[ch] = 1; 
        lst = 1; ans = 0; 
        for(re int i = 1; i <= n; i ++)
            if(f[s[i]]) ans = max(ans, i - lst), lst = i; 
        cout << ans << "\n"; 
    }   
    return 0;
}
```
  - **核心实现思想**：利用数组f标记特殊字符，遍历字符串s，遇到特殊字符时更新ans（最大距离）和lst（上一个特殊字符位置），最后输出ans。

- **作者：ttq012 (4星)**
  - **关键亮点**：对特殊字符操作数量的解释清晰，代码逻辑明确，使用vector和map处理数据。
  - **核心代码**：
```cpp
void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int k;
    cin >> k;
    vector <char> arr(k);
    map <char, bool> alp;
    for (int i = 0; i < k; i ++)
        cin >> arr[i];
    for (int i = 0; i < k; i ++)
        alp[arr[i]] = true;
    vector <int> id;
    for (int i = 0; i < n; i ++)
        if (alp[s[i]])
            id.push_back(i);
    if (id.empty()) {
        puts("0");
        return ;
    }
    int ans = id[0];
    for (int i = 1; i < (int) id.size(); i ++)
        ans = max(ans, id[i] - id[i - 1]);
    cout << ans << '\n';
}
```
  - **核心实现思想**：用map标记特殊字符，vector存储特殊字符位置，先特判无特殊字符情况，再计算并更新最大距离ans。

### 最优关键思路或技巧
1. **思维方式**：将复杂的字符串操作问题转化为求特殊字符间最长距离的问题，简化问题求解。
2. **代码实现技巧**：部分题解使用数组标记特殊字符，遍历一次字符串即可得出结果，提高效率；有的题解采用快速读入优化，避免超时。

### 同类型题或类似算法套路拓展
同类型题通常围绕字符串操作与特定规则下的计数或最值求解。类似套路是分析操作规则，转化为简单的数学关系（如距离、数量等），通过遍历字符串并结合合适的数据结构（如数组、map等）记录状态来解决问题。

### 洛谷相似题目推荐
1. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：涉及字符串匹配与计数，需对字符串进行遍历和判断。
2. [P1593 因子和阶乘](https://www.luogu.com.cn/problem/P1593)：结合数学知识与字符串处理，分析数字在阶乘中的因子情况。
3. [P2219 数的分解](https://www.luogu.com.cn/problem/P2219)：通过枚举和字符串操作，按要求分解数字。 

---
处理用时：73.63秒