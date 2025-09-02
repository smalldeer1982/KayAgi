# 题目信息

# awoo's Favorite Problem

## 题目描述

### 翻译


你会得到两个长度为 $n$ 的字符串 $s$ 和 $t$。 两个字符串中的每个字符都是`a`、`b`或`c`。

在一个操作中，您可以执行其中之一：

选择 $s$ 中出现的 `ab` 并将其替换为 `ba` ；

选择 $s$ 中出现的 `bc` 并将其替换为    `cb`。

您可以执行任意数量的移动（可能为零）。 您可以更改字符串 $s$ 以使其等于字符串 $t$ 吗？

## 样例 #1

### 输入

```
5
3
cab
cab
1
a
b
6
abbabc
bbaacb
10
bcaabababc
cbbababaac
2
ba
ab```

### 输出

```
YES
NO
YES
YES
NO```

# AI分析结果

### 题目内容重写
# awoo's Favorite Problem

## 题目描述

你会得到两个长度为 $n$ 的字符串 $s$ 和 $t$。两个字符串中的每个字符都是`a`、`b`或`c`。

在一个操作中，您可以执行其中之一：

- 选择 $s$ 中出现的 `ab` 并将其替换为 `ba`；
- 选择 $s$ 中出现的 `bc` 并将其替换为 `cb`。

您可以执行任意数量的移动（可能为零）。您可以更改字符串 $s$ 以使其等于字符串 $t$ 吗？

## 样例 #1

### 输入

```
5
3
cab
cab
1
a
b
6
abbabc
bbaacb
10
bcaabababc
cbbababaac
2
ba
ab
```

### 输出

```
YES
NO
YES
YES
NO
```

### 算法分类
字符串

### 题解分析与结论
本题的核心在于通过有限的操作（`ab` -> `ba` 和 `bc` -> `cb`）将字符串 $s$ 转换为字符串 $t$。所有题解都基于以下关键观察：
1. `a` 只能向后移动，`c` 只能向前移动。
2. 去掉所有 `b` 后，$s$ 和 $t$ 必须相同。
3. `a` 和 `c` 的相对位置不能改变。

题解的主要思路是通过遍历字符串，检查 `a` 和 `c` 的位置是否符合上述条件，并确保 `b` 的数量一致。

### 精选题解

#### 题解1：linyuhuai (5星)
**关键亮点**：
- 通过删除 `b` 后直接比较 $s$ 和 $t$，简化了问题。
- 使用双指针遍历，确保 `a` 和 `c` 的位置关系正确。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
void solve(){
    int n;
    scanf("%d",&n);
    std::string s,t;
    std::cin>>s;
    std::cin>>t;
    int j=0;
    int sb=0,sb2=0;//sum of 'b'
    for(int i=0;i<n;i++){
        while(t[j]=='b')sb2++,j++;
        if(s[i]=='b'){sb++;continue;}
        if(s[i]!=t[j]||s[i]=='a'&&i>j||s[i]=='c'&&i<j){
            puts("NO");
            return;
        }
        j++;
    }
    while(t[j]=='b')sb2++,j++;
    if(sb!=sb2){
        puts("NO");
        return;
    }
    puts("YES");
    return;
}
```

#### 题解2：alex_liu (4星)
**关键亮点**：
- 通过记录 `b` 的数量，确保 $s$ 和 $t$ 中 `b` 的数量一致。
- 使用快读优化，提高了输入效率。
- 代码结构清晰，易于理解。

**核心代码**：
```cpp
signed main(){
    n=read();
    while(n--){
        string s1,s2;
        int len=read(),cnt1=0,cnt2=0;
        cin>>s1>>s2;
        for(int i=0;i<len;i++){
            if(!(s1[i]^'b'))cnt1++;
            if(!(s2[i]^'b'))cnt2++;	
        }
        if(cnt1^cnt2)puts("NO");
        else{
            int x=0,f=0;
            for(int i=0;i<len;i++){
                if(!(s1[i]^'b'))continue;
                while(!(s2[x]^'b'))x++;
                if(s1[i]^s2[x]||(!(s1[i]^'a')&&i>x)||(!(s1[i]^'c')&&i<x)){f=1;puts("NO");break;}
                x++;
            }
            if(!f)puts("YES");
        }
    }
    return 0;
}
```

#### 题解3：fast_photon (4星)
**关键亮点**：
- 使用队列记录每个 `b` 前面的 `a` 和 `c` 的数量，确保 `a` 和 `c` 的位置关系正确。
- 代码实现较为复杂，但逻辑严谨，适合深入理解问题。

**核心代码**：
```cpp
void solve() {
    while(!A.empty()) A.pop();
    while(!C.empty()) C.pop(); 
    ss = tt = "";
    a = c = 0;
    cin >> n;
    cin >> s >> t;
    for(int i = 0; i < n; i++) {
        if(s[i] == 'a') a++, ss += 'a'; 
        if(s[i] == 'c') c++, ss += 'c';
        if(s[i] == 'b') {
            A.push(a);
            C.push(c);
        }
    }
    a = c = 0;
    for(int i = 0; i < n; i++) {
        if(t[i] == 'a') a++, tt += 'a';
        if(t[i] == 'c') c++, tt += 'c';
        if(t[i] == 'b') {
            if(A.empty()) {
                printf("NO\n");
                return;
            }
            if(!(A.front() >= a && C.front() <= c)) { 
                printf("NO\n");
                return;
            }
            A.pop();
            C.pop();
        }
    }
    if(ss != tt) {
        printf("NO\n");
        return;
    }
    printf("YES\n");
}
```

### 最优关键思路
1. **删除 `b` 后直接比较**：通过删除所有 `b` 后比较 $s$ 和 $t$，简化了问题。
2. **双指针遍历**：使用双指针确保 `a` 和 `c` 的位置关系正确。
3. **记录 `b` 的数量**：确保 $s$ 和 $t$ 中 `b` 的数量一致。

### 拓展思路
类似的问题可以通过观察字符的移动规律，利用双指针或队列等数据结构来简化问题。例如，处理字符串中的特定字符替换或移动问题时，可以先去掉无关字符，再进行比较或操作。

### 推荐题目
1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042)

---
处理用时：39.79秒