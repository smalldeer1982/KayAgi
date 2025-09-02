# Stalin Sort

## 题目描述

Stalin Sort 是一种有趣的排序算法，旨在消除不合适的元素，而不是贪心地对它们进行正确排序，从而将自己时间复杂度变为$ \mathcal{O}(n) $。

它是这样进行的：从数组中的第二个元素开始，如果它严格小于前一个元素（忽略那些已经被删除的元素），则删除它。继续遍历数组，直到它按非降序排序。例如，数组$ [1, 4, 2, 3, 6, 5, 5, 7, 7] $经过斯大林排序后的结果是$ [1, 4, 6, 7, 7] $。

如果您可以通过对数组的任何子数组$ ^{\text{∗}} $重复应用 Stalin Sort 来使数组以非递增顺序排序，那么我们将这样的数组定义为vulnerable，根据需要可以多次调用。

给定一个含$ n $个整数的数组$ a $，确定最少需要从数组中删除几个整数，才能让这个数组变得vulnerable。

 $ ^{\text{∗}} $如果数组$ a $可以通过由数组$ b $从头部和尾部删除几个（可以是零个或者所有）元素获得，那么我们认为数组$ a $是数组$ b $的子数组。

## 说明/提示

在第1个输入输出样例中，最佳答案是删除数字$ 3 $和$ 9 $.然后我们只剩下$ a = [6, 4, 2, 5, 2] $.为了使这个数组变得脆弱，我们可以首先对子数组$ [4, 2, 5] $应用 Stalin Sort来获得$ a = [6, 4, 5, 2] $，然后在子数组$ [6, 4, 5] $上应用 Stalin Sort来获得非递增的数组$ a = [6, 2] $

在第2个输入输出样例中，数组已经是非递增的了，因此不必删除任何数。

题面翻译来自[映月之晴](https://www.luogu.com.cn/user/505433)

## 样例 #1

### 输入

```
6
7
3 6 4 9 2 5 2
5
5 4 4 2 2
8
2 2 4 4 6 6 10 10
1
1000
9
6 8 9 10 12 9 7 5 4
7
300000000 600000000 400000000 900000000 200000000 400000000 200000000```

### 输出

```
2
0
6
0
4
2```

# 题解

## 作者：Super_Cube (赞：4)

# Solution

只要一个数组中的第一个数是最大值，那么后面的数都可以用斯大林排序给干掉。于是枚举 $i$ 为最大值，把前面 $i-1$ 个数删完，还要删后面比 $i$ 大的个数，最终对每个位置答案取 $\min$。

---

## 作者：Stars_Traveller (赞：2)

## CF2027B Stalin Sort 题解
### 分析
对题意中给出的 Stalin 排序的定义进行分析。

我们需要让原数列单调不降，则每一次枚举最大值，在它前面的就都比它小，需要删除，共 $i-1$ 个数。而在它后面的比它小的一样需要删除。

需要使删除个数最小，枚举 $a_i$，$a_i$ 前面的元素全部删除，$a_i$ 后面的比它大的元素也需删除。计算每个枚举到的元素的成本，取最小值即为答案。

### 代码
```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[10005], t, n;
signed main()
{
	for(cin>>t;t;t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		int minn=1e18;
		/*
		每次统计在他后面比他大的，再加上他前面的i-1个数即为当前i的成本，取最小值
		*/
		for(int i=1;i<=n;i++){int cnt=0;for(int j=i+1;j<=n;j++)if(a[j]>a[i])cnt++;minn=min(minn,cnt+i-1);}
		cout<<minn<<"\n";
	}
}

---

## 作者：Sakura_Emilia (赞：1)

# Solution

题意读起来稍微有点难以理解，但结合样例的话还是很好理解的。题目问的是最少可以去掉几个数之后，剩下的数可以用多次斯大林排序将序列变为非递增的。这恰好与斯大林排序的检查规则相反。

思考最终得到的非递增数组，一定是原数组的子序列。来依次枚举每一个位置，相当于检查每一个位置来执行多次斯大林排序的情况。由于需要求的是最少删除个数，因此来对每一个位置进行检查，检查**每一个数后面比它大的数的个数加前面的总个数**，找出最小值，即为答案。

# Code

Java 版本代码实现：

```java
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] x = new int[100000];
        Scanner in = new Scanner(System.in);
        int T = in.nextInt();
        while ((T--) > 0) {
            int n = in.nextInt();
            for (int i = 1; i <= n; i++) {
                x[i] = in.nextInt();
            }

            int Min = Integer.MAX_VALUE;
            for (int i = 1; i <= n; i++) {
                int t = 0;
                for (int j = i + 1; j <= n; j++) {
                    if (x[j] > x[i]) {
                        t++;
                    }
                }
                Min = Math.min(Min, t + i - 1);
            }
            
            System.out.println(Min);
        }
    }
}
```

---

## 作者：Stars_visitor_tyw (赞：0)

## 题解：CF2027B Stalin Sort
### 分析
读题中关于 Stalin 排序的信息，观察到需要最后留下一个单调不降子序列。

考虑枚举元素，对于每个当前枚举到的元素 $a_i$，$a_i$ 前面的元素全部删除，$a_i$ 后面的比它大的元素也需删除。计算每个枚举到的元素的成本，取最小值即为答案。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[114514], t, n;
signed main()
{
	for(cin>>t;t;t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		int mini=1145141919810;
		for(int i=1;i<=n;i++)
		{
			int tmp=0;
			for(int j=i+1;j<=n;j++)
			{
				if(a[j]>a[i])tmp++;
			}
			mini=min(mini,tmp+i-1);
		}
		cout<<mini<<"\n";
	}
}

---

## 作者：Dollartree (赞：0)

### 题目思路
基于斯大林排序的规则，我们的目标是选定某个元素 $a_i$，并消除 $a_i$ 前面的所有元素以及 $a_i$ 后面所有比 $a_i$ 大的元素，所以枚举选定一个元素，消除它前面的所有元素以及后面比它大的元素，遍历找出最小值即可。
### 题目代码
[记录1](https://vjudge.net/solution/55951341)
[记录2](https://codeforces.com/contest/2027/submission/291313566)

```cpp
#include<bits/stdc++.h>
const int INF=99999999;
using namespace std;
int a[2010];
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;++i)
		{
			scanf("%d",&a[i]);
		}
		int mmin=INF,cnt;
		for(int i=1;i<=n;++i)
		{
			cnt=0;
			cnt+=i-1;//前面都被删除了
			for(int j=i+1;j<=n;++j)
			{
				if(a[i]<a[j])//这个数字会被消去的情况
				{
					cnt++;
				}
			}
			mmin=min(cnt,mmin);
		}
		printf("%d\n",mmin);
	}
 } 
```

---

## 作者：fanjiayu666 (赞：0)

### 题目大意
其实这个斯大林排序本意是将一段区间内的一些数删掉，留下一个单调不降子序列。

而题目是给定一个序列，问至少删去几个数可以用多次斯大林排序将序列变为非递增的。
### 思路
首先，我们可以发现，序列肯定是由多个单调不升子序列组成的，如样例：
$$3 \, 6 \, 4\, 9\,2 \,5 \,2$$

由 $[3],[6,4],[9,2],[5,2]$，组成。

所以我们处理时就遍历一遍，如果第 $i$ 个数违反单调不降（即单调不升子序列的开头）的就以它为开头，把前面的 $i-1$ 个都删掉，统计后面有多少个 $>a_i$ 的数，总成本为 $i-1+t$（$t$ 是后面 $>a_i$ 的数的个数），然后对所有成本取 $\min$ 即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n;
int a[10010],ans;
int main(){
    cin>>t;
    while(t--){
        ans=0;
        cin>>n;
        ans=n-1;
        for(int i=1;i<=n;i++)cin>>a[i];//输入不用说。
        int it=1;
        while(it<n){
        	while(a[it]<a[it+1]&&it<n){
        		it++;
        	}//寻找单调不降子序列的开头（即违反单调不降的数）
        	if(it>=n)break;
        	int tmp=a[it],tmp2=it,cnt=0;
        	while(tmp2<=n){
        		if(a[tmp2]>tmp)cnt++;
        		tmp2++;
        	}//往后看有没有大于它的
        	if(it+cnt-1<ans)ans=it+cnt-1;//取min
        	it++;//记得往后一位，否则会卡死。
        }
        cout<<ans<<endl;//输出答案
    }
  return 0;//华丽的结束
}
```

---

