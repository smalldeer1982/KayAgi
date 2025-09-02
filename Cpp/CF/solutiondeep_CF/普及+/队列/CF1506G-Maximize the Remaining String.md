# 题目信息

# Maximize the Remaining String

## 题目描述

给你一个由小写英文字母组成的字符串 $s$，你需要去掉一部分字符，使得操作后得到的字符串 $t$ 满足在 $s$ 中出现的字母每种只保留一个并且最大化 $t$ 的字典序。

## 样例 #1

### 输入

```
6
codeforces
aezakmi
abacaba
convexhull
swflldjgpaxs
myneeocktxpqjpz```

### 输出

```
odfrces
ezakmi
cba
convexhul
wfldjgpaxs
myneocktxqjpz```

# AI分析结果

### 题目内容
# 最大化剩余字符串

## 题目描述
给你一个由小写英文字母组成的字符串 $s$，你需要去掉一部分字符，使得操作后得到的字符串 $t$ 满足在 $s$ 中出现的字母每种只保留一个并且最大化 $t$ 的字典序。

## 样例 #1
### 输入
```
6
codeforces
aezakmi
abacaba
convexhull
swflldjgpaxs
myneeocktxpqjpz
```
### 输出
```
odfrces
ezakmi
cba
convexhul
wfldjgpaxs
myneocktxqjpz
```

### 综合分析与结论
这些题解的核心思路都是贪心策略，主要围绕如何在满足每个字母仅出现一次的条件下，构造出字典序最大的子序列。
 - **思路方面**：多数题解采用从前往后遍历原字符串，借助辅助数据结构（如单调栈、数组、map等）来决定当前字符是否加入结果序列。若当前字符字典序大于栈顶字符且栈顶字符后续还会出现，则弹出栈顶字符，以保证字典序最大。
 - **算法要点**：需记录每个字符出现的次数或最后出现的位置，同时标记字符是否已在结果序列中。通过这些信息，在遍历过程中动态调整结果序列。
 - **解决难点**：关键在于如何平衡字典序最大和每个字符仅出现一次这两个条件。既要保证当前加入的字符能使字典序增大，又要确保不会因删除某些字符而导致后续无法满足每个字符都出现的要求。

### 所选的题解
 - **作者：liangbowen (5星)**
    - **关键亮点**：思路清晰，详细阐述了单调栈的使用方法及每一步操作的原因，代码注释详尽，对初学者友好。
    - **个人心得**：强调多测不清空，爆零两行泪，提醒注意多测试用例时数据的初始化。
    - **重点代码**：
```cpp
void solve()
{
    memset(cnt, 0, sizeof(cnt)); //多测不清空，爆零两行泪！！！
    memset(instk, false, sizeof(instk));
    string s;
    cin >> s;
    int len = s.length();
    for (int i = 0; i < len; i++) cnt[s[i] - 'a']++;
    stack <int> stk; //单调栈 
    for (int i = 0; i < len; i++)
    {
        int x = s[i] - 'a';
        if (!instk[x])
        {
            while (!stk.empty() && cnt[stk.top()] && x > stk.top()) instk[stk.top()] = false, stk.pop();
            stk.push(x), instk[x] = true; //没进栈就进栈 
        }
        cnt[x]--; //删除掉一个
    }
    string ans = "";
    while (!stk.empty()) ans += (stk.top() + 'a'), stk.pop();
    reverse(ans.begin(), ans.end());
    cout << ans << '\n';
}
```
核心实现思想：利用单调栈，遍历字符串，根据字符是否在栈中、栈顶字符与当前字符字典序以及字符剩余次数来决定是否弹出栈顶字符，最后从栈中获取结果并反转。

 - **作者：SpeedStar (4星)**
    - **关键亮点**：算法分析简洁明了，指出本题与力扣上“去除重复字母”为类似题目，代码简洁，使用STL容器。
    - **重点代码**：
```cpp
while (t--) {
    string s, stk;
    cin >> s;
    map<char, bool> ins;
    map<char, int> last;
    for (int i = 0; i < s.size(); ++i) last[s[i]] = i;
    
    rep(i, s.size()) {
        if (ins[s[i]]) continue;
        while (stk.size() and stk.back() < s[i] and last[stk.back()] > i) {
            ins[stk.back()] = false;
            stk.pop_back();
        }
        stk += s[i];
        ins[s[i]] = true;
    }
    
    cout << stk << '\n';
}
```
核心实现思想：使用两个map，一个记录字符是否在结果字符串中，另一个记录字符最后出现的位置。遍历字符串，若字符不在结果字符串中，根据结果字符串最后字符与当前字符字典序及最后出现位置决定是否删除结果字符串最后字符，最后得到结果字符串。

 - **作者：YangXiaopei (4星)**
    - **关键亮点**：采用贪心策略，全篇使用string，实现思路独特，通过维护两个数组来记录字符出现次数和是否在结果字符串中，代码易读。
    - **重点代码**：
```cpp
for(int i = 0; i < n; i++){
    f[s[i] - 'a']++;
}
for(int i = 0; i < n; i++){
    f[s[i] - 'a']--;
    if(t.size() == 0){
        t = t + s[i];
        vis[s[i] - 'a'] = 1;
    }
    else if(vis[s[i] - 'a']){
        continue;
    }
    else{
        while(t.size() > 0 && t[t.size() - 1] < s[i] && f[t[t.size() - 1] - 'a'] > 0){
            vis[t[t.size() - 1] - 'a'] = 0;
            t = t.substr(0, t.size() - 1);
        }
        t = t + s[i];
        vis[s[i] - 'a'] = 1;
    }
}
```
核心实现思想：先统计每个字符出现次数，遍历字符串时，根据结果字符串是否为空、当前字符是否已在结果字符串中以及结果字符串最后字符与当前字符字典序和剩余次数来决定是否删除结果字符串最后字符并加入当前字符。

### 最优关键思路或技巧
使用单调栈或类似结构，结合记录字符出现次数或最后出现位置的辅助数据结构，在遍历字符串过程中，基于贪心思想动态调整结果序列，保证字典序最大且每个字符仅出现一次。

### 可拓展之处
同类型题通常围绕字符串子序列构造，要求满足特定条件下最大化或最小化字典序等。类似算法套路是利用贪心策略，借助栈、数组等数据结构，在遍历过程中根据字符间关系和条件动态调整结果。

### 推荐题目
 - [P2893 [USACO08FEB]Making the Grade G](https://www.luogu.com.cn/problem/P2893)
 - [P3957 [NOIP2017 提高组] 跳房子](https://www.luogu.com.cn/problem/P3957)
 - [P4072 [SDOI2016]征途](https://www.luogu.com.cn/problem/P4072)

---
处理用时：36.72秒