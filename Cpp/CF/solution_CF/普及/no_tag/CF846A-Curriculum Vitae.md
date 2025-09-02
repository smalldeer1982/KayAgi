# Curriculum Vitae

## 题目描述

Hideo Kojima has just quit his job at Konami. Now he is going to find a new place to work. Despite being such a well-known person, he still needs a CV to apply for a job.

During all his career Hideo has produced $ n $ games. Some of them were successful, some were not. Hideo wants to remove several of them (possibly zero) from his CV to make a better impression on employers. As a result there should be no unsuccessful game which comes right after successful one in his CV.

More formally, you are given an array $ s_{1},s_{2},...,s_{n} $ of zeros and ones. Zero corresponds to an unsuccessful game, one — to a successful one. Games are given in order they were produced, and Hideo can't swap these values. He should remove some elements from this array in such a way that no zero comes right after one.

Besides that, Hideo still wants to mention as much games in his CV as possible. Help this genius of a man determine the maximum number of games he can leave in his CV.

## 样例 #1

### 输入

```
4
1 1 0 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
6
0 1 0 0 1 0
```

### 输出

```
4
```

## 样例 #3

### 输入

```
1
0
```

### 输出

```
1
```

# 题解

## 作者：泠小毒 (赞：3)

# Curriculum Vitae
给你一个长度为n的01序列a，删去其中的几个数，使得序列中左边是连续的0，右边是连续的1，可以没有0或1，求最多剩下几个数
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190514/)

[博客园(同步更新)](https://www.cnblogs.com/muronglin/p/hgoi-20190514.html)
## 解法
对于每个点看它左边几个0，右边几个1，弄个前缀和可以O(n)，虽然n方也能过QAQ
## ac代码
```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,a[110],suml[110],sumr[110],ans=0;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)suml[i]=suml[i-1]+(a[i]==0);
	for(int i=n;i>=1;i--)sumr[i]=sumr[i+1]+(a[i]==1);
	for(int i=1;i<=n;i++)ans=max(ans,suml[i]+sumr[i]);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：lukelin (赞：2)

枚举一个点，假设它一定符合条件，据此珂以$O(n)$算出要删去几个点  
于是就$O(n^2)$解决了，貌似加一个前缀和可以在$O(n)$的时间复杂度内解决本问题，但对于这个数据范围来说$O(n^2)$戳戳有余

放个代码：
```cpp
#include <cstdio> 
#define ll long long

inline ll read(){
    ll x = 0; int zf = 1; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

int a[105];

int main(){
    int n = read();
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    int ans = 0, cnt;
    for (int i = 1; i <= n; ++i){
        cnt = 0;
        for (int j = i + 1; j <= n; ++j)
            if (!a[j])
                ++cnt;
        for (int j = 1; j < i; ++j)
            if (a[j])
                ++cnt;
        if (n - cnt > ans)
            ans = n - cnt;
    }
    printf("%d", ans);
    return 0;
}
```

---

## 作者：刘子懿 (赞：1)

# Solution:

思路：求左 $0$ 的个数加右边 $1$ 的个数，再取最大值。

方法：可以用前缀和来维护区间，复杂度为 $O(n)$ 。

### code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,add[120];
int main(){
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1; i<=n; i++){
        cin>>add[i];//前缀和
        add[i]+=add[i-1];
    }
    for(int i=0; i<=n; i++){//注意从0开始
        ans=max(ans,(i+add[n]-2*add[i]));//左边0的个数为i-add[i]，右边1的个数为add[n]-add[i]
    }
    cout<<ans;
    return 0;//好习惯
}
```


---

## 作者：刘子懿 (赞：1)

思路：求左边有几个 $0$ ，右边有几个 $1$ ，再取最大值。

方法：可以用前缀和来维护区间，复杂度为 $O(n)$ 。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,add[120];
int main(){
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1; i<=n; i++){
        cin>>add[i];//前缀和
        add[i]+=add[i-1];
    }
    for(int i=0; i<=n; i++){//注意从0开始
        ans=max(ans,(i+add[n]-2*add[i]));//左边0的个数为i-add[i]，右边1的个数为add[n]-add[i]
    }
    cout<<ans;
    return 0;//好习惯
}
```


---

## 作者：zplqwq (赞：0)

首先我们考虑 $O(n^2)$ 的做法。

即，我们枚举每一个点，假设我们要统计这个点，用 $O(n)$ 的复杂度暴力求出要删去几个点。


其次我们考虑 $O(n)$ 的做法。

首先正着跑一遍前缀和，求出左边有几个 $0$，设为 $x_i$。同理，反着跑一遍前缀和，求出右边有几个 $1$ $y_i$ 。最后答案是 $\max(x_i,y_i)$ 。

这个套路感觉还是很常见的。



---

## 作者：灵光一闪 (赞：0)

哇，好像我的并不是O($n^2$)啊，感觉很开森，特写篇题解庆祝~

具体看代码
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

#include<vector>
using namespace std;
int a[233];
vector<int> v;
int ans;
bool flag=false;
int main(){
    int sum=1,num;
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
        if(i){//这一串是把 0011001处理成2221的形式，这样可以配成一对一对的，这样下面好算
            if(a[i]==a[i-1]){
                sum++;
            }
            else{
                if(a[i-1]==1||flag){
                    v.push_back(sum);//记录了
                }
                else{
                    ans+=sum;//前面的所有0直接保留
                }
                flag=true;
                sum=1;
            }
        }
    }
    v.push_back(sum);
    if(v.size()%2==1){//如果是奇数就再压一个0进去
        v.push_back(0);
    }
/*
for(int i=0;i<v.size();i++){//把注释去掉就可以看清楚v数组了
    cout<<v[i]<<" ";
}
return 0;
*/
    sum=0,num=0;
    for(int i=0;i<v.size()-1;i+=2){
        sum+=v[i];//是1
        num+=v[i+1];//是0
        if(sum<num){//如果1的个数要大于0的个数就直接把1掐掉
            ans+=num;
            sum=0;
            num=0;
        }
        /*
        这里有必要说明一下：为什么1的个数大于等于0不掐掉0
        因为如果是这种情况呢？
        1010000000000000
        此时绝对是把两个1掐掉划算对吧？
        但是如果1的个数大于等于0就掐掉0的话
        先把第一个0掐掉，然后就是
        110000000000000
        这时候明显是掐掉两个1，但是那个0却冤枉地被掐掉了（0：我招你惹你了qaq）
        然后如果1的个数大于等于0不掐掉0的话
        1010000000000000
        1和1相等了，所以看下面：
        两个一和若干个0（不想数，反正比2大……）相比，明显是0多，所以掐掉2个1
        那为什么0的个数要大于1的个数就要直接把1掐掉呢？
        比如这组数据：
        11000011111
        现在明显看到：前面一组中1有两个，0有4个
        如果我们选择掐掉0，很明显不值得
        而留到后面去完全没必要，因为把前面两个1干掉那4个0就是合法的了，所以肯定选择掐掉前面的1，后面？我不管~反正那4个1都合法了，保留，肯定是好的
        然后我们又是从前面开始往后扫的，所以前面要么是全0，要么就是前面的1顽强抵抗，一直拖到这来了，如果是全零，那就你好我好大家好嘛，如果有1反抗，那不就是持一种“能解决战斗就解决，解决不了往后拖”的策略嘛，如果到最后也没有结束战斗（0没1多）那答案就是合法的0+全部的1啊，如果赢了就把前面的1全部掐掉，就留0，然后继续判断……
        */
    }
    cout<<ans+max(sum,num)<<endl;//最后再做一次判断
    return 0;
}
```
The End.

---

