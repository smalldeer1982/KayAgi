# Minimum Difficulty

## 题目描述

Mike is trying rock climbing but he is awful at it.

There are $ n $ holds on the wall, $ i $ -th hold is at height $ a_{i} $ off the ground. Besides, let the sequence $ a_{i} $ increase, that is, $ a_{i}<a_{i+1} $ for all $ i $ from 1 to $ n-1 $ ; we will call such sequence a track. Mike thinks that the track $ a_{1} $ , ..., $ a_{n} $ has difficulty ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF496A/6c4805b013b934a5f994bca3651000871cc18881.png). In other words, difficulty equals the maximum distance between two holds that are adjacent in height.

Today Mike decided to cover the track with holds hanging on heights $ a_{1} $ , ..., $ a_{n} $ . To make the problem harder, Mike decided to remove one hold, that is, remove one element of the sequence (for example, if we take the sequence $ (1,2,3,4,5) $ and remove the third element from it, we obtain the sequence $ (1,2,4,5) $ ). However, as Mike is awful at climbing, he wants the final difficulty (i.e. the maximum difference of heights between adjacent holds after removing the hold) to be as small as possible among all possible options of removing a hold. The first and last holds must stay at their positions.

Help Mike determine the minimum difficulty of the track after removing one hold.

## 说明/提示

In the first sample you can remove only the second hold, then the sequence looks like $ (1,6) $ , the maximum difference of the neighboring elements equals 5.

In the second test after removing every hold the difficulty equals 2.

In the third test you can obtain sequences $ (1,3,7,8) $ , $ (1,2,7,8) $ , $ (1,2,3,8) $ , for which the difficulty is 4, 5 and 5, respectively. Thus, after removing the second element we obtain the optimal answer — 4.

## 样例 #1

### 输入

```
3
1 4 6
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5
1 2 3 7 8
```

### 输出

```
4
```

# 题解

## 作者：Reobrok_Kk (赞：1)

#### 水题

看题貌似要加什么优化，实际上不用，看数据：$1 \le n \le 100$，直接 $O(n^2)$ 暴力枚举每一种删数情况。

需要注意的是要加一个指针记录上一个没被删的数，枚举到被删了的数时直接 `continue` 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[105];
int main() {
    int n, ans = 2147483647; //答案初始化
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 2; i < n; ++i) { //枚举2~n-1每个数被删的情况
        int chayi = -1, last = 1; //last指针初始化，差异值初始化
        for (int j = 2; j <= n; ++j) {
            if (j == i) continue; //枚举到了要删的数，跳过
            chayi = max(abs(a[j] - a[last]), chayi); //更新差异值
            last = j; //这个数不被删，last指针才会赋值，避免没有删掉
        }
        ans = min(chayi, ans); //更新答案
    }
    cout << ans << endl;
}

```

---

## 作者：Insouciant21 (赞：1)

好水的题（（（STL大法好

$n\leq100$ 直接暴力，尝试每一个可以进行删除的位置，如样例
```
5
1 2 3 7 8
```
删去一个数后有如下情况：
```
1 3 7 8 7-3=4
1 2 7 8 7-2=5
1 2 3 8 8-3=5
```

即答案为 $4$

AC代码如下

``` cpp
#include <bits/stdc++.h>

using namespace std;

int n;
int ans = 0x3f3f3f;
vector<int> num;

int main() {
    scanf("%d", &n);
    for (int i = 1, t; i <= n; i++) {
        scanf("%d", &t);
        num.push_back(t);
    }
    for (int i = 1; i < n - 1; i++) {
        int diff = -1;
        vector<int> s(num);
        s.erase(next(s.begin(), i));
        for (auto iter = s.begin() + 1; iter != s.end(); iter++) diff = max(diff, *iter - *(iter - 1)); // 求每一个排列的差值
        ans = min(ans, diff);
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：清小秋ovo (赞：0)

# CF469A 题解

这题还蛮简单的。看到数据范围直接打暴力

枚举删掉每一个数之后的差异值，并取所有情况的最小值即可。

```cpp
#include<bits/stdc++.h>

using namespace std;

int n, ans = 1e9, a[105];

int solve(int x){
    int d = -1;
    for(int i=2;i<=n;i++) d = max(d,a[i]-a[i-1]);
    return max(d,a[x+1]-a[x-1]);
}

int main()
{
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=2;i<n;i++) ans = min(ans,solve(i));
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：flywan123 (赞：0)

### 这道题其实在黄题中算比较简单的 （~~但难倒了本蒟蒻~~）
## 这道题我的解决方法是：把每一个位置都试一次，在这些试出的结果中取最小值
举一个例子：
输入

5

1 2 3 4 5

第一个位置：1 3 4 5 为2

第二个位置：1 2 4 5 为2

第三个位置：1 2 3 5 为2

其中的最小值为2

所以答案就是2

放上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,a[1001]={0},min=10001;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    for(int i=2;i<n;i++)
    {
        int max=0;
        for(int j=1;j<i-1;j++)
        {
            if(abs(a[j+1]-a[j])>max)
            {
                max=abs(a[j+1]-a[j]);//删除之前的部分
            }
        }
        if(abs(a[i+1]-a[i-1])>max)
        {
            max=abs(a[i+1]-a[i-1]);//特殊地方
        }
        for(int j=i+1;j<n;j++)
        {
            if(abs(a[j+1]-a[j])>max)
            {
                max=abs(a[j+1]-a[j]);//后面的部分
            }
        }
        if(max<min)
        {
            min=max;//取最小值
        }
    }
    cout<<min;//完工
    return 0;
}
```


---

## 作者：codemap (赞：0)

用了一种比较无脑的方法

先用一个数组记录相邻两数的差

对其排序后从2到n-1扫一遍

分两种情况

若a[i]-a[i-1]是最大的差异值,结果=min(结果,max(第二大的差异值,a[i+1]-a[i-1]))

否则结果=min(结果,max(最大差异值,a[i+1]-a[i-1]))

上代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	int n,a[101],i,mmin=1000000,b[101];//b是差异值数组
	cin>>n;
	for(i=1;i<=n;i++)
		cin>>a[i];
	for(i=2;i<=n;i++)
		b[i-1]=a[i]-a[i-1];//计算差异值(注意是i-1)
	sort(b+1,b+n);//排序(注意是b+n)
	for(i=2;i<n;i++)//不能去两边
	{
		if(a[i]-a[i-1]==b[n-1])//第一种情况
			mmin=min(mmin,max(b[n-2],a[i+1]-a[i-1]));//更新最小值
		else//否则
			mmin=min(mmin,max(b[n-1],a[i+1]-a[i-1]));//更新最小值
	}
	cout<<mmin;//输出最小值
	return 0;//完美结束
}
```
# 请勿抄袭

---

