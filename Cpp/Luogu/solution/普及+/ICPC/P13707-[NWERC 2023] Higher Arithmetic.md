# [NWERC 2023] Higher Arithmetic

## 题目描述

验证码（Captchas）正变得越来越复杂。最初只是简单的计算，比如 $7+2$，而现在甚至需要区分吉娃娃狗和双层巧克力松饼（如下图所示）。

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/uvk9ao3u.png)
:::

为了对抗更智能的机器人，互联网验证码生产公司（Internet Captcha Production Company, ICPC）这次使出了绝招：
给定一个扭曲的图像，其中包含多个整数，你需要使用每个整数恰好一次，通过加法、乘法及任意括号组合，构造一个表达式，使其计算结果最大。

Katrijn 尝试解决这类验证码一小时未果，感到极度沮丧。她决定编写一个程序，输出一个具有最大值的有效算术表达式。

## 样例 #1

### 输入

```
4
1 2 3 4```

### 输出

```
3*((1+2)*4)```

## 样例 #2

### 输入

```
3
13 37 1```

### 输出

```
(1+13)*37```

## 样例 #3

### 输入

```
4
1 1 1 1```

### 输出

```
((1+1)*(1+1))```

# 题解

## 作者：Frozen_Ladybug (赞：1)

### 题目大意

给你 $n$ 个数字，让你用括号、加号和乘号搭配，使得你所组成的式子按照你的运算后所得的值最大。

### 解

一般来讲，加号不如乘号，只有个别的数字要处理，其他都用乘号。

题目对答案的正确判断一定是根据你的式子运算后的数值判断正确，所以对于括号要求不严格。

>令 $k$ 个 $1$ 合成 $k$，$k+1$ 个 $1$ 合成 $k+1$，若一共有 $n$ 个 $1$，那么运算的式子就是 $k^{\frac{n}{k}}<(k+1)^{\frac{n}{k+1}}$。
>
>两边同时取对数，再消去 $n$，即 $\frac{\ln k}{k}<\frac{\ln(k+1)}{k+1}$。
>
>而 $\frac{\ln x}{x}$ 的导数为 $\frac{1-\ln x}{x^2}$，故它在 $e$ 处取最大值，且它在 $3$ 处的函数值比在 $2$ 处大，所以需要尽可能多的凑出 $3$。

对于其余无法凑出 $3$ 的数，如果剩下 $1$ 个，只能把 $1$ 加入前面或者后面，后面的数字一定是大于等于 $3$，如果是 $3$，加入前面后面都一样；如果后面不是 $3$，加入前面更好，这样两边更趋近一些，乘积更大。

所以剩余一个 $1$ 尽量给前面，剩下两个 $1$ 就把 $(1+1)$ 乘进去就行了。

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll dp[3],n;
int main(){
    cin>>n;
    priority_queue<ll, vector<ll>, greater<ll>> q;
    for(ll i=1;i<=n;i++){
        ll x;
        cin>>x;
        if (x==1||x==2) dp[x]++;
        else q.push(x);
    }
    string ans; 
    if(dp[1]<=dp[2]){
        for(ll i=1;i<=dp[1];i++) ans+="(1+2)*"; 
        dp[2]-=dp[1],dp[1]=0;
        while(dp[2]--)  ans+="2*";
    }
    else if(dp[1]){
        bool ok=0;
        for(int i=1;i<=dp[2];i++){
            ans+="(1+2)*";
            ok=1;
        }
        dp[1]-=dp[2],dp[2]=0;
        int cnt=dp[1]/3;
        int r=dp[1]%3;
        while(cnt--){
            ans+="(1+1+1)*";
            ok=1;
        }
        if(r==1){
            if(ok){
                ans[ans.size() - 2]='+';
                ans[ans.size() - 1]='1';
                ans+=")*";
            }
            else if(q.size()>0){
                int x=q.top();
                q.pop();
                string s;
                while(x){
                    s=char(x%10+'0')+s;
                    x/=10;
                }
                ans=ans+"(1+"+s+")*";
            }
            else ans+="1*";
        }
        else if(r==2) ans+="(1+1)*";
    }
    if(ans.size())
        for(int i=0;i<ans.size()-1;i ++) cout<<ans[i];
    bool ok=0;
    while(q.size()){
        if(ans.size()||ok) cout<<"*";
        ok=1;
        cout<<q.top();
        q.pop();
    }
    return 0;
}
```

---

