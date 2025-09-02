# Guest Student

## 题目描述

Berland State University invites people from all over the world as guest students. You can come to the capital of Berland and study with the best teachers in the country.

Berland State University works every day of the week, but classes for guest students are held on the following schedule. You know the sequence of seven integers $ a_1, a_2, \dots, a_7 $ ( $ a_i = 0 $ or $ a_i = 1 $ ):

- $ a_1=1 $ if and only if there are classes for guest students on Sundays;
- $ a_2=1 $ if and only if there are classes for guest students on Mondays;
- ...
- $ a_7=1 $ if and only if there are classes for guest students on Saturdays.

The classes for guest students are held in at least one day of a week.

You want to visit the capital of Berland and spend the minimum number of days in it to study $ k $ days as a guest student in Berland State University. Write a program to find the length of the shortest continuous period of days to stay in the capital to study exactly $ k $ days as a guest student.

## 说明/提示

In the first test case you must arrive to the capital of Berland on Monday, have classes on this day, spend a week until next Monday and have classes on the next Monday. In total you need to spend $ 8 $ days in the capital of Berland.

## 样例 #1

### 输入

```
3
2
0 1 0 0 0 0 0
100000000
1 0 0 0 1 0 1
1
1 0 0 0 0 0 0
```

### 输出

```
8
233333332
1
```

# 题解

## 作者：Yamchip (赞：3)

## 题意
给定 $k$ 和 $a_{1}$ 到 $a_{7}$，$a_{i}$ 表示这周的第 $i$ 天是否有课时,求学习时长为 $k$ 的学习天数。
## 思路
打个暴力和模拟，时限妥妥够，从每个有课时的那一天开始模拟，先算整数周，再枚举剩余天数，最后统计一下天数最小值。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t, a[10], k, ans, cnt, sum, ansa;
int main()
{
    cin >> t;
    while(t--)
    {
        cin >> k;
        sum = 0;//每周课时天数
        ansa = 2e9;//这个测试用例的总答案
        for(int i = 1;i <= 7;i++)
        {
        	cin >> a[i];
        	if(a[i]) sum++;
        }
        for(int i = 1;i <= 7;i++)
        {
            if(a[i])
			{
    			cnt = 0;//一周内有课时的那一天后还有多少课时
        		ans = 0;//本次答案
				for(int j = i;j <= 7;j++)
	        	if(a[j]) cnt++;
		        ans = k / sum * 7 - 7;
		        if(k % sum == 0) ans -= 7;//如果天数能被这周课时数整除那就再模拟一遍最后一周的情况
		        int m = k - ans / 7 * sum - cnt;//剩余天数
		        while(m)//防止最后一周补不完剩余天数
		        {
			        for(int j = 1;j <= 7;j++)
			        {
			            if(a[j] && m > 0)
			            	m--;
			            ans++;
			            if(m == 0) break;
			        }
			    }
			    ansa = min(ansa, ans + 7 - i + 1);//记得加上第一周的天数
			}
        }
        cout << ansa << endl;
    }
    return 0;
}
```

---

## 作者：Harrylzh (赞：2)

可以把题目看成一个环：

![](https://cdn.luogu.com.cn/upload/image_hosting/ena5eb8h.png)

安排为 `1 0 0 0 1 0 1` 时的情况
                                
思路：问题就可以看成任意选一个开始点，顺时间方向走，使得刚好经过 $k$ 个黑点，求最小的总经过点数。如上图，一圈有三个黑点，所以每需要经过三个黑点，就一定需要走七个点。剩下不足三个的部分，就枚举每种情况取最优方案即可。

细节：

1. 最好的方案一定是黑点开始，黑点结束，所以可以先不考虑最后一个黑点，再在最后加上，方便处理。

2. 可以处理出每个黑点到下一个黑点前需要经过的点数，方便取最小值。

代码：
```cpp
#include<iostream>
#include<cstring>
using namespace std;
int t;
int k;
bool a[15];
int b[15];
int main()
{
    cin>>t;
    while(t--)
    {
    	memset(b,0,sizeof(b));
        cin>>k;
        k--;//减去最后一个点
        int s=0;
        for(int i=1;i<=7;i++) cin>>a[i],s+=a[i];
        for(int i=8;i<=14;i++) a[i]=a[i-7];//环的处理方法
        int ans=k/s*7;//周期部分
        for(int i=1;i<=7;i++)
        {
            if(a[i])
            {
                b[i]=1;
                for(int j=i+1;!a[j];j++)
                {
                    b[i]++;
                }
            }
        }
        for(int i=8;i<=14;i++) b[i]=b[i-7];
        k%=s;
        int minn=2e9;
        for(int i=1;i<=7;i++)
        {
            int d=0;
            if(a[i]==0) continue;
            for(int j=i,c=1;c<=k;c++,j+=b[j]) d+=b[j];//只枚举黑点
            minn=min(minn,d);
        }
        ans+=minn;
        ans++;//加上最后一个点
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：pyz51 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1089G)

[CF传送门](https://codeforces.com/problemset/problem/1089/G)

[AC记录](https://codeforces.com/contest/1089/submission/293367754)
# 题意简述
给定 $k$ 和 $a_1$ 到 $a_7$，$a_i$ 表示这周的第 $i$ 天是否有课时，求学习时长为 $k$ 的学习天数。~~（翻译太简洁了，直接粘过来）~~
# 题解
先考虑一次学习一整周，直接 $\left\lceil\dfrac{k}{\sum_{i = 1}^7 a_i}\right\rceil$ 算出学了几周。  
接下来是最后一周中要学几天。  
**注意，一周中开始可以是任意一天。**  
也就是说，这一周可以是周一 $\to$ 周二 $\to\cdots\to$ 周天，也可以是周二 $\to$ 周三 $\to\cdots\to$ 周一。  
当然，这件事对前面的整周没影响，但最后一周，调换顺序可以改变答案，所以最后枚举开头周一 $\sim$ 周天，取 $\min$，再加上前面的整周，即为答案。
# AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
const int M=2e5+5;
const int inf=2147483647;
const long long lof=9223372036854775807;
#define ll long long
#define bug cout<<"...here...\n"
#define mem(a,b) memset(a,b,sizeof a)
#define CLOSE ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define F first
#define S second
inline ll read(){
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int Stack[105];
inline void print(ll x){
    int cnt=0;
    if(x<0) putchar('-'),x=-x;
    while(x){
    	Stack[++cnt]=x%10;
    	x/=10;
    }
    while(cnt--) putchar((char)Stack[cnt+1]+'0');
    return;
}
int t,k,a[15];
int main(){
    CLOSE
    cin>>t;
    while(t--){
        cin>>k;
        int sum=0;
        for(int i=1;i<=7;i++) cin>>a[i],a[i+7]=a[i],sum+=a[i];
        int ans=(k+sum-1)/sum*7-7,minn=inf;//计算前面的整周
        k%=sum;
        if(k==0) k+=sum;
        for(int i=1;i<=7;i++){//枚举一周的开头
            int now=0;
            for(int j=0;j<7;j++){
                now+=a[j+i];
                if(now>=k){
                    minn=min(minn,j+1);//取min
                    break;
                }
            }
        }
        cout<<ans+minn<<'\n';
    }
    return 0;
}
```

---

