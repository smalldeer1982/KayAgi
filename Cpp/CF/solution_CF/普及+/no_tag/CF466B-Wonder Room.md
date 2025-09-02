# Wonder Room

## 题目描述

伴随着新学年的开始，学生们在宿舍住宿出现了问题。其中每一间宿舍有一个 $a\times b$ 平方米的房间。宿管想在那里正好容纳 $n$ 个学生。但学校的要求规定，每个学生的房间必须至少有 $6$ 平方米（也就是说，$n$ 名学生的房间必须至少有 $6n$ 平方米的面积）。宿管可以将房间的任何一侧（可能是两侧）扩大任意正整数米。请你帮助他扩建房间，使 $n$ 个学生都能住在里面，且使房间的总面积尽可能小。

------------

## 样例 #1

### 输入

```
3 3 5
```

### 输出

```
18
3 6
```

## 样例 #2

### 输入

```
2 4 4
```

### 输出

```
16
4 4
```

# 题解

## 作者：TheShuMo (赞：3)

## 思路
我们可以简化一下题意：在满足 $n$ 个学生能住在这间宿舍时，使宿舍的总面积最小，其中每个学生需要 $6m^2$ 的面积。

在这的基础上我们就可以知道，这间宿舍最小面积是$6nm^2$。
于是长宽之和最短就是 $\sqrt{6nm^2}$ 即 $\sqrt{6n}m$。

进而，我们就可以从 $1m$ 开始枚举其中一条边 $a$ 的长度，直到
$\sqrt {6n}m$。同时，在枚举每一个 $a$ 的值时，用 $\lceil6n\div a\rceil$ 得到 $b$ 的值，计算 $a \times b$ 与当前最小面积 $minn$ 的大小并替换。这种枚举下就可以以 $ O(\sqrt{n})$ 的复杂度枚举完成，不会超时。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    long long a,b,n,flag=0;long long minn=1145141919810;//求最小设极大
    cin>>n>>a>>b;
    n*=6;
    if(a*b>=n){
        cout<<a*b<<endl;
        cout<<a<<" "<<b;
        return 0;
    }if(a>b)swap(a,b),flag=1;//如果换过位置就标记
    long long temp,ansa,ansb;
    for(int i=a;i<=sqrt(n);i++){
        temp=n/i;if(temp*i<n)temp++;
        if(temp>=b&&minn>=temp*i){
            minn=temp*i;
            ansa=i;
            ansb=temp;
        }
    }if(flag)swap(ansa,ansb);//有标记则交换
    cout<<ansa*ansb<<"\n"<<ansa<<" "<<ansb;
    return 0;
}
```


---

## 作者：loser_seele (赞：2)

首先，既然需要每个学生有6平方米的空间，则新的边长必须大于等于 $ 6n $ 。

现在假设 $ a \leq b $ （不满足可以交换），则可以枚举 $ a $ 的取值去计算出新的满足条件的最小的 $ b $ ，然后如果当前面积比目前面积小就更新答案。

因为 $ a \leq b $ ，所以 $ a $ 枚举到 $ \sqrt{6n} $ 即可。

时间复杂度 $ O(\sqrt{n}) $ 。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
int a,b,n;
cin>>n>>a>>b;
if(a*b>6*n)//本来就满足条件
{
cout<<a*b<<'\n';
cout<<a<<' '<<b;
return 0;
}
bool ok=0;
if(a>b)//交换
swap(a,b),ok=1;
int inf=1e18,ansa=0,ansb=0;
for(int i=a;i<=sqrt(6*n);i++)//枚举新的a
{
int now=6*n/i;
if(now*i<6*n)
now++;
if(now>=b&&inf>=now*i)//更新答案
inf=now*i,ansa=i,ansb=now;
}
if(ok)//交换
swap(ansa,ansb);
cout<<inf<<'\n';
cout<<ansa<<' '<<ansb;
}
```

---

## 作者：Ruan_ji (赞：1)

这道题不是特别难，模拟即可，但是坑点极多。

写本题时需要注意的地方：

- 这道题目是需要暴力枚举，但是必须枚举完。具体的说，就是不能得到一个答案就直接 ```return 0;```  因为题目强调了：**“且使房间的总面积尽可能小”**。举个例子，如果你的代码跟下文所示的一样，就过不了。
```cpp
 for (int i = 1;i <= n; ++i) {
        answer = a * b;
        if (answer >= n) {
            cout << answer << endl;
            cout << a << " " << b;
            return 0; //就是这里需要比较，而不是直接输出
        }
        b += 1;
    }
```
- 数据范围极大，不开 ```long long``` 会见祖宗。

- 我们上文也提到了，需要从头到尾遍历一遍，才能输出最后最小的答案。但是数据范围极其无情: $ 1\leq n \leq 1e9$ 。那么，我们必须遍历，但是一遍历就会超时，这不是个死结吗？当然不是，我们并不用整个遍历，直接遍遍历到   $\sqrt{\smash[b]{n}}$  即可。这样，就大大节省了时间。

- 最后一点，我们要确定遍历的变量是谁，不能弄错了。所以，就直接遍历第一个数字好了，而且保证第一个数字比第二个数字大。如果初始值不是这样，交换位置即可。

综上，就可以开始模拟了~
## AC code
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
long long n, a, b;
long long answer = 1e18, answer_a, answer_b;
long long flag;

int max (int a, int b) {
    if (a >= b) return a;
    else return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie (0); cout.tie (0);

    cin >> n >> a >> b; n *= 6;
    if (a > b) {
        swap (a, b);
        flag = true;
    }
    
    for (int i = 1;i <= sqrt (n); ++i) { //遍历到根号 n 就行
        int x = i, y = (n + i - 1) / i;
        x = max (a, x); y = max (b, y);
        if (x * y < answer) { //如果比原数小，更新
            answer = x * y;
            answer_a = x;
            answer_b = y;
        }
    }
    
    cout << answer << '\n'; //注意使用关同步不能用endl
    if (flag == true) cout << answer_b << " " << answer_a;
    else cout << answer_a << " " << answer_b;
}
```


---

## 作者：s_c_lmlm_L (赞：0)

### 题意：
一名学生所需 $6m^2$的房间。
现有宿舍面积为 $abm^2$，求拓宽任意边正整数米，使满足 $n$ 名学生下最小面积是多少？


------------


已知一名学生所需 $6m^2$的房间，所以 $n$ 名学生所需 $6nm^2$。
理想长宽为 $\sqrt{6n}$ 

所以我们只需要枚举最短边延长到$\sqrt{6n}$，来满足另外一边尽可能短。

设：$a$ 为最短边，令 $a=a',b=b'$，有
$$\min\Big(a'b'\Big)≥6n$$
代码为：
```cpp
for(int i=a;i<=sqrt(6*n);i++)//枚举a~sqrt(6*n)
    {
        ll m=6*n/i;
        if(m*i<6*n)
            m++;
        if(m>=b&&minx>m*i)//尽可能小
        {
            minx=m*i;//更新最小值
            x=i;
            y=m;
        }    
    }
```

通过样例二我们可以看出 $6n≤ab$，
所以我们可以以做一个小小的优化
```cpp
if(6*n<=a*b)
    {
        cout<<a*b<<endl<<a<<" "<<b;
        return 0;//当6*n<=a*b
    }
```

自认为上面已经讲的够清楚了，接下来公布$\xcancel{\text{安全无注释 } }$代码


# $AC$ $code$

```cpp
#include<iostream>
#include<cmath>
using namespace std;
#define ll long long
ll n,a,b,minx=1e18,x=0,y=0;
bool flag=false;
int main()
{
    cin>>n>>a>>b;
    if(6*n<=a*b)
    {
        cout<<a*b<<endl<<a<<" "<<b;
        return 0;
    }
    if(a>b)
    {
        swap(a,b);
        flag=true;
    }    
    
    for(int i=a;i<=sqrt(6*n);i++)
    {
        ll m=6*n/i;
        if(m*i<6*n)
            m++;
        if(m>=b&&minx>m*i)
        {
            minx=m*i;
            x=i;
            y=m;
        }    
    }
    if(flag)
        swap(x,y);
    cout<<minx<<endl<<x<<" "<<y;
}
//抄题解是不好的行为
```


---

