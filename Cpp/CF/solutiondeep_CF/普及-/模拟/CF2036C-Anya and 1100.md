# 题目信息

# Anya and 1100

## 题目描述

While rummaging through things in a distant drawer, Anya found a beautiful string $ s $ consisting only of zeros and ones.

Now she wants to make it even more beautiful by performing $ q $ operations on it.

Each operation is described by two integers $ i $ ( $ 1 \le i \le |s| $ ) and $ v $ ( $ v \in \{0, 1\} $ ) and means that the $ i $ -th character of the string is assigned the value $ v $ (that is, the assignment $ s_i = v $ is performed).

But Anya loves the number $ 1100 $ , so after each query, she asks you to tell her whether the substring "1100" is present in her string (i.e. there exist such $ 1 \le i \le |s| - 3 $ that $ s_{i}s_{i + 1}s_{i + 2}s_{i + 3} = \texttt{1100} $ ).

## 样例 #1

### 输入

```
4
100
4
1 1
2 0
2 0
3 1
1100000
3
6 1
7 1
4 1
111010
4
1 1
5 0
4 1
5 0
0100
4
3 1
1 1
2 0
2 1```

### 输出

```
NO
NO
NO
NO
YES
YES
NO
NO
YES
YES
YES
NO
NO
NO
NO```

# AI分析结果

### 题目中文重写
### Anya与1100

#### 题目描述
在翻找一个遥远抽屉里的东西时，Anya发现了一个漂亮的字符串 $s$，该字符串仅由0和1组成。

现在她想通过对其进行 $q$ 次操作，让它变得更加漂亮。

每次操作由两个整数 $i$（$1 \le i \le |s|$）和 $v$（$v \in \{0, 1\}$）描述，这意味着将字符串的第 $i$ 个字符赋值为 $v$（即执行赋值操作 $s_i = v$）。

但Anya喜欢数字 $1100$，所以每次查询后，她会让你告诉她，她的字符串中是否存在子串 "1100"（即是否存在 $1 \le i \le |s| - 3$ 使得 $s_{i}s_{i + 1}s_{i + 2}s_{i + 3} = \texttt{1100}$）。

#### 样例 #1
##### 输入
```
4
100
4
1 1
2 0
2 0
3 1
1100000
3
6 1
7 1
4 1
111010
4
1 1
5 0
4 1
5 0
0100
4
3 1
1 1
2 0
2 1
```

##### 输出
```
NO
NO
NO
NO
YES
YES
NO
NO
YES
YES
YES
NO
NO
NO
NO
```

### 综合分析与结论
这些题解的核心目标都是解决在每次修改字符串中一个字符后，判断字符串中是否存在子串 "1100" 的问题。它们的共性在于都意识到直接暴力枚举会超时，所以都采用了优化策略，即只考虑修改位置附近的子串变化来更新结果。

- **思路对比**：
    - 部分题解（如Scean_Tong、xingshuyan000）通过维护一个计数器 `cnt` 来记录 "1100" 子串的数量，每次修改后更新计数器。
    - 部分题解（如zhang_kevin、Starlit_Night）使用 `set` 来存储 "1100" 子串的起始位置，修改后更新 `set`。
    - 部分题解（如Sakura_Emilia）通过分类讨论修改位置的前后情况来更新子串数量。
- **算法要点**：
    - 所有题解都需要先预处理出初始字符串中 "1100" 子串的情况。
    - 每次修改时，只检查修改位置附近（通常是前后3个位置）的子串变化。
- **解决难点**：
    - 关键在于如何高效地更新子串信息，避免每次都遍历整个字符串。通过只关注修改位置附近的子串，将时间复杂度从 $O(q \cdot |s|)$ 优化到 $O(n + q)$。

### 所选题解
- **Scean_Tong（5星）**
    - **关键亮点**：思路清晰，代码简洁易懂，通过维护计数器 `ans` 来记录 "1100" 子串的数量，每次修改后更新计数器。
    - **核心代码**：
```cpp
bool check(int pos){
    return s[pos]=='1'&&s[pos+1]=='1'&&s[pos+2]=='0'&&s[pos+3]=='0';
}
void solve(){
    cin>>s>>q;
    ans=0;
    int n=s.size();
    s='#'+s;
    for(int i=1;i<=n-3;i++){
        if(check(i)){
            ans++;
        }
    }
    while(q--){
        int i,v;
        cin>>i>>v;
        for(int k=max(1ll,i-3);k<=min(n,i+4);k++){
            if(check(k)){
                ans--;
            }
        }
        s[i]=v^'0';
        for(int k=max(0ll,i-3);k<=min(n,i+4);k++){
            if(check(k)){
                ans++;
            }
        }
        if(ans){
            cout<<"Yes"<<'\n';
        }
        else cout<<"No"<<'\n';
    }
}
```
- **zhang_kevin（4星）**
    - **关键亮点**：使用 `set` 存储 "1100" 子串的起始位置，修改后更新 `set`，思路巧妙，易于理解。
    - **核心代码**：
```cpp
set<int> s;
inline void Solve(){
    s.clear();
    string str;
    cin >> str;
    bool Last = false;
    for(int i = 0; i < str.length() - 3; i++){
        if(str[i] == '1' && str[i+1] == '1' && str[i+2] == '0' && str[i+3] == '0'){
            s.insert(i);
            Last = true;
        }
    }
    int q; cin >> q;
    while(q--){
        int pos, v;
        cin >> pos >> v;
        pos--;
        if(str[pos] == v + '0'){
            output(Last);
            continue;
        }else{
            str[pos] = v + '0';
            for(int i = max(0, pos-3); i <= pos; i++){
                if(str[i] == '1' && str[i+1] == '1' && str[i+2] == '0' && str[i+3] == '0'){
                    if(s.count(i)!= 0){
                        Last = true;
                    }else{
                        s.insert(i);
                        Last = true;
                    }
                }else{
                    if(s.count(i)!= 0){
                        s.erase(i);
                        if(s.empty()){
                            Last = false;
                        }else{
                            Last = true;
                        }
                    }
                }
            }
            output(Last);
        }
    }
    return;
}
```
- **xingshuyan000（4星）**
    - **关键亮点**：详细分析了暴力解法的超时原因，并给出了优化思路，代码实现简洁明了。
    - **核心代码**：
```cpp
void solve()
{
    string s;
    cin >> s;
    int cnt = 0, n = s.length();
    for(int i = 0; i < n; i ++)
    {
        if(s.substr(i, 4) == "1100") cnt ++;
    }
    int q;
    cin >> q;
    while(q--)
    {
        int i;
        char v;
        cin >> i >> v;
        i --;
        int p1 = 0, p2 = 0;
        if(s[i]!= v)
        {
            for(int j = max(i - 3, 0); j <= min(i, n - 3); j ++)
            {
                if(s.substr(j, 4) == "1100") p1 = 1;
            }
            s[i] = v;
            for(int j = max(i - 3, 0); j <= min(i, n - 3); j ++)
            {
                if(s.substr(j, 4) == "1100") p2 = 1;
            }
            cnt += p2 - p1;
        }
        if(cnt) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return;
}
```

### 最优关键思路或技巧
- **维护关键信息**：通过维护 "1100" 子串的数量或起始位置，避免每次修改后都遍历整个字符串。
- **局部更新**：只关注修改位置附近的子串变化，将时间复杂度从 $O(q \cdot |s|)$ 优化到 $O(n + q)$。

### 可拓展之处
- **同类型题**：类似的字符串修改后查询特定子串的问题，如查询其他固定长度的子串。
- **算法套路**：可以使用类似的维护关键信息和局部更新的方法来解决。

### 推荐洛谷题目
- [P1165 日志分析](https://www.luogu.com.cn/problem/P1165)
- [P1996 约瑟夫问题](https://www.luogu.com.cn/problem/P1996)
- [P2058 海港](https://www.luogu.com.cn/problem/P2058)

### 个人心得
题解中未包含个人心得内容。

---
处理用时：37.40秒