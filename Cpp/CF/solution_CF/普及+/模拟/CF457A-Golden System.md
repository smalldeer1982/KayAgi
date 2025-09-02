# Golden System

## 题目描述

### 完整题意
Piegirl 已经对二进制、十进制以及其他整数计数系统感到厌倦。最近她发现了关于数字 $q=\frac{\sqrt5+1}{2}$ 的一些有趣的性质，特别是当 $q^2=q+1$ 时，并且她认为这将为她的独特的新系统打下良好基础。她管这叫“黄金系统”。在黄金系统中，数字是包含 $0$ 与 $1$ 的非空字符串，表达式 $a_0a_1\dots a_n$ 的十进制值为 $\sum_{i=0}^{n}a_i\times q^{i-1}$。

很快她就发现这个系统不具有基础整数计数系统的性质，并且有些操作无法在这上面执行。她无法想出一种快速比较两个数的方法，于是来向你求助。

给出两个用黄金系统表示的数，比较哪个数更大。

## 样例 #1

### 输入

```
1000
111
```

### 输出

```
<```

## 样例 #2

### 输入

```
00100
11
```

### 输出

```
=
```

## 样例 #3

### 输入

```
110
101
```

### 输出

```
>```

# 题解

## 作者：N_z_ (赞：2)

## 思路
注意到$q^2=q+1$，变形得$q^i=q^{i-1}+q^{i-2}$。

不断降次直至只剩两次为止即可。

两次后直接暴力判断就可以了。

可以把两个数组提前作差，最后与$0$比较大小。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
double aa[100001];
signed main(){
    string a,b;
    cin>>a>>b;
    int fa=100000-a.length()+1,fb=100000-b.length()+1;
    for(int x=0;x<a.length();x++)
    aa[100000-a.length()+x+1]=a[x]-'0';
    for(int x=0;x<b.length();x++)
    aa[100000-b.length()+x+1]-=b[x]-'0';
    for(int x=min(fa,fb),y;x<=100000-2;x++)
    aa[x+1]+=aa[x],aa[x+2]+=aa[x],aa[x]=0;
    double ans=double(aa[99999]*(1+sqrt(5))/2+aa[100000]);
    //cout<<ans<<endl;
    if(abs(ans)<=1e-8)cout<<'=';
    else if(ans<0)cout<<'<';
    else cout<<'>';
}
```

---

## 作者：jasonshen_ (赞：0)



### 完整题意
Piegirl 已经对二进制、十进制以及其他整数计数系统感到厌倦。最近她发现了关于数字 $q=\frac{\sqrt5+1}{2}$ 的一些有趣的性质，特别是当 $q^2=q+1$ 时，并且她认为这将为她的独特的新系统打下良好基础。她管这叫“黄金系统”。在黄金系统中，数字是包含 $0$ 与 $1$ 的非空字符串，表达式 $a_0a_1\dots a_n$ 的十进制值为 $\sum_{i=0}^{n}a_i\times q^{i-1}$。

很快她就发现这个系统不具有基础整数计数系统的性质，并且有些操作无法在这上面执行。她无法想出一种快速比较两个数的方法，于是来向你求助。

给出两个用黄金系统表示的数，比较哪个数更大。

### 思路

观察题目，我们可以知道，我们只需暴力枚举直至只剩两次为止即可。

两次后直接暴力判断就可以了。

### 代码
```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const ll N = 200200;

void Fix(string& s)
{
    reverse(s.begin(),s.end());

    s.resize(N,'0');

    for(ll i=N-1;i>0;i--)
        while( i<N-1 && s[i]=='1' && s[i-1]=='1' )
            s[i] = s[i-1] = '0' , s[i+1] = '1' , i++ , i++ ;

    reverse(s.begin(),s.end());
}

int main()
{
    string s1;  cin>>s1;    Fix(s1);
    string s2;  cin>>s2;    Fix(s2);

    if(s1==s2)  cout<<"=";
    if(s1>s2)   cout<<">";
    if(s1<s2)   cout<<"<";
}
```

---

