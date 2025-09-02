# ZgukistringZ

## 题目描述

Professor GukiZ doesn't accept string as they are. He likes to swap some letters in string to obtain a new one.

GukiZ has strings $ a $ , $ b $ , and $ c $ . He wants to obtain string $ k $ by swapping some letters in $ a $ , so that $ k $ should contain as many non-overlapping substrings equal either to $ b $ or $ c $ as possible. Substring of string $ x $ is a string formed by consecutive segment of characters from $ x $ . Two substrings of string $ x $ overlap if there is position $ i $ in string $ x $ occupied by both of them.

GukiZ was disappointed because none of his students managed to solve the problem. Can you help them and find one of possible strings $ k $ ?

## 说明/提示

In the third sample, this optimal solutions has three non-overlaping substrings equal to either $ b $ or $ c $ on positions $ 1–2 $ ( $ ab $ ), $ 3–4 $ ( $ ab $ ), $ 5–7 $ ( $ aca $ ). In this sample, there exist many other optimal solutions, one of them would be $ acaababbcc $ .

## 样例 #1

### 输入

```
aaa
a
b
```

### 输出

```
aaa```

## 样例 #2

### 输入

```
pozdravstaklenidodiri
niste
dobri
```

### 输出

```
nisteaadddiiklooprrvz```

## 样例 #3

### 输入

```
abbbaaccca
ab
aca
```

### 输出

```
ababacabcc```

# 题解

## 作者：QQH08 (赞：0)

这题我一开始想的是贪心，直接先满足所有 b,再看剩下多少 c。或者先满足所有 c，再看剩下多少b。但卡在 test $12$ 过不去了。

下面考虑正解。

首先，很显然调换字母只要满足字母数量够就行了。

先算出有多少个 b 和 c 能从 a 中凑出来，记作 ans1 和 ans2。

如果 $ans1 > ans2$，就枚举 b 凑几个出来，然后看剩下还能凑出多少个 c（记作 res ）。每次更新答案。

否则就枚举凑几个 c，再凑 b。

必须枚举数量多的那个，否则出现 $ans1=0,ans2 \neq 0$，枚举b就会炸。

最后把剩下的一起输出。

代码实现很简单：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
string a,b,c;
int ans1=1e9,ans2=1e9,ans,tot1,tot2,mp1[26],mp2[26],mp3[26],cnt[26];
int main(){
    cin>>a>>b>>c;
    int n1=a.length(),n2=b.length(),n3=c.length();
    for(int i=0;i<n1;i++)mp1[a[i]-'a']++;
    for(int i=0;i<n2;i++)mp2[b[i]-'a']++;
    for(int i=0;i<n3;i++)mp3[c[i]-'a']++;
    for(int i=0;i<26;i++){
        if(mp2[i])ans1=min(ans1,mp1[i]/mp2[i]);
        if(mp3[i])ans2=min(ans2,mp1[i]/mp3[i]);
    }
    if(ans1>ans2){
        for(int i=1;i<=ans1;i++){
            int res=1e9;
            for(int j=0;j<26;j++)cnt[j]=mp1[j];
            for(int j=0;j<26;j++)cnt[j]-=i*mp2[j];
            for(int j=0;j<26;j++)
                if(mp3[j])res=min(res,cnt[j]/mp3[j]);
            if(i+res>ans){
                ans=i+res;
                tot1=i,tot2=res;
            }
        }
    }
    else{
        for(int i=1;i<=ans2;i++){
            int res=1e9;
            for(int j=0;j<26;j++)cnt[j]=mp1[j];
            for(int j=0;j<26;j++)cnt[j]-=i*mp3[j];
            for(int j=0;j<26;j++)
                if(mp2[j])res=min(res,cnt[j]/mp2[j]);
            if(i+res>ans){
                ans=i+res;
                tot2=i,tot1=res;
            }
        }
    }
    for(int i=0;i<26;i++){
        if(mp2[i])mp1[i]-=tot1*mp2[i];
        if(mp3[i])mp1[i]-=tot2*mp3[i];
    }
    for(int i=1;i<=tot1;i++)cout<<b;
    for(int i=1;i<=tot2;i++)cout<<c;
    for(int i=0;i<26;i++)
        for(int j=1;j<=mp1[i];j++)cout<<char('a'+i);
    return 0;
}
```


---

