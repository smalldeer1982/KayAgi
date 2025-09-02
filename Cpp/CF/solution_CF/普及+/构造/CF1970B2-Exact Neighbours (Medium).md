# Exact Neighbours (Medium)

## 题目描述

The only difference between this and the hard version is that $ a_{1} = 0 $ .

After some recent attacks on Hogwarts Castle by the Death Eaters, the Order of the Phoenix has decided to station $ n $ members in Hogsmead Village. The houses will be situated on a picturesque $ n\times n $ square field. Each wizard will have their own house, and every house will belong to some wizard. Each house will take up the space of one square.

However, as you might know wizards are very superstitious. During the weekends, each wizard $ i $ will want to visit the house that is exactly $ a_{i} $ $ (0 \leq a_{i} \leq n) $ away from their own house. The roads in the village are built horizontally and vertically, so the distance between points $ (x_{i}, y_{i}) $ and $ (x_{j}, y_{j}) $ on the $ n\times n $ field is $  |x_{i} - x_{j}| + |y_{i} - y_{j}| $ . The wizards know and trust each other, so one wizard can visit another wizard's house when the second wizard is away. The houses to be built will be big enough for all $ n $ wizards to simultaneously visit any house.

Apart from that, each wizard is mandated to have a view of the Hogwarts Castle in the north and the Forbidden Forest in the south, so the house of no other wizard should block the view. In terms of the village, it means that in each column of the $ n\times n $ field, there can be at most one house, i.e. if the $ i $ -th house has coordinates $ (x_{i}, y_{i}) $ , then $ x_{i} \neq x_{j} $ for all $ i \neq j $ .

The Order of the Phoenix doesn't yet know if it is possible to place $ n $ houses in such a way that will satisfy the visit and view requirements of all $ n $ wizards, so they are asking for your help in designing such a plan.

If it is possible to have a correct placement, where for the $ i $ -th wizard there is a house that is $ a_{i} $ away from it and the house of the $ i $ -th wizard is the only house in their column, output YES, the position of houses for each wizard, and to the house of which wizard should each wizard go during the weekends.

If it is impossible to have a correct placement, output NO.

## 说明/提示

For the sample, the house of the 1st wizard is located at $ (4, 4) $ , of the 2nd at $ (1, 3) $ , of the 3rd at $ (2, 4) $ , of the 4th at $ (3, 1) $ .

The distance from the house of the 1st wizard to the house of the 1st wizard is $ |4 - 4| + |4 - 4| = 0 $ .

The distance from the house of the 2nd wizard to the house of the 1st wizard is $ |1 - 4| + |3 - 4| = 4 $ .

The distance from the house of the 3rd wizard to the house of the 1st wizard is $ |2 - 4| + |4 - 4| = 2 $ .

The distance from the house of the 4th wizard to the house of the 3rd wizard is $ |3 - 2| + |1 - 4| = 4 $ .

The view and the distance conditions are satisfied for all houses, so the placement is correct.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1970B2/9f9f415b711c20a1d43262d4b959c18fec467842.png)

## 样例 #1

### 输入

```
4
0 4 2 4```

### 输出

```
YES
4 4
1 3
2 4
3 1
1 1 1 3```

## 样例 #2

### 输入

```
4
0 1 3 1```

### 输出

```
YES
1 1
2 1
4 1
3 1
1 1 1 3```

# 题解

## 作者：0tAp (赞：1)

题目链接：[Exact Neighbours (Medium)](https://www.luogu.com.cn/problem/CF1970B2)


------------
简单构造和模拟。

思路：根据题意可知一列只能放 $1$ 个房子，因此我们从左向右开始进行构造，因为 $a_1=0$ 因此我们将第一个房屋放在 $(1,1)$ 便于进行后面的处理，考虑接下来的 $j$ 和 $a_j$，如果 $a_j-j+1$ 刚好等于 $0$ ，说明此房屋和 $1$ 号房屋在同一行时，刚好能走到 $1$ 号房，那么我们就将该房屋放在第 $j$ 列，第 $1$ 行，并指向第一个房屋，如果 $a_j-j+1>0$，那么我们只需要将其向上移动即可，即将该房屋放在第 $j$ 列，第 $a_j-j+2$ 行，并让该房屋指向第一个房屋，如果 $a_j-j+1<0$，那么我们就找离他刚好这个距离的房屋即可，即放置在第 $j$ 列，第 $y_{i-a_i}$ 行（这里的 $y$ 指刚好距离所需放置房屋 $a_j$ 的目标房屋的行数）。

按这个操作从左到右构造下去一定能得到一个合法的方案，因为在 $a_i\le n$ 的情况下每个房子都能根据其距离到一个合法的位置，因此每个房子都能有一个合法的位置。


------------
代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define dwn(i,a,b) for(int i=(a);i>=(b);i--)

void solve(){
	int n;
	scanf("%d",&n);
	vector<int>a(n+10),x(n+10),y(n+10),ans(n+10);
	rep(i,1,n)scanf("%d",&a[i]);
	if(a[1]){cout<<"NO";return;}
	x[1]=1,y[1]=1;
	ans[1]=1;
	rep(i,2,n){
		if(!a[i]){x[i]=i,y[i]=1,ans[i]=i;continue;}
		int now=a[i]-i+1;
		if(now==0){x[i]=i,y[i]=1;ans[i]=1;continue;}
		if(now>0){x[i]=i,y[i]=now+1;ans[i]=1;continue;}
		else{x[i]=i,y[i]=y[-now+1],ans[i]=-now+1;continue;}
	}
	puts("YES");
	rep(i,1,n)printf("%d %d\n",x[i],y[i]);
	rep(i,1,n)printf("%d ",ans[i]);return;
} 

int main()
{
	solve();
	return 0;
}
```

---

## 作者：FFTotoro (赞：1)

[点这里前往游记。](https://www.luogu.com.cn/article/u3edqf6r)

下文中所有下标从 $0$ 开始；称一栋房子的“目标”为其主人周末会去哪栋房子做客；因为每一列恰好有一栋房子，所以从左到右建房子。

因为 $a_0=0$，所以对于第一栋房子的目标设为其本身即可。

对于后面的房子，可以考虑直接根据前面已经建好的房子进行建造。具体地，如果 $a_i=0$ 那么随便建；如果 $a_i\ge i$ 那么就将 $0$ 号房子作为目标，去掉往左走到第 $0$ 列的贡献，可以轻易地确定这栋房子要建在第几列（因为 $a_i\le n\Rightarrow a_i-i<n$ 并且 $0$ 号房子在第 $0$ 行，直接将其建在第 $a_i-i$ 列即可）；如果 $a_i<i$ 那么直接找到前面和它距离 $a_i$ 的列，然后跟那一列上的房子建在同一行上即可。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  int n; cin>>n;
  vector<int> a(n),r(n),l(n);
  for(auto &i:a)cin>>i;
  if(!a[0]){ // B2 的特殊性质
    cout<<"YES\n1 1"<<endl,r[0]=1;
    for(int i=1;i<n;i++){
      if(!a[i]){cout<<i+1<<" 1\n",r[i]=1,l[i]=i; continue;}
      int x=a[i]-i;
      if(x>=0)cout<<i+1<<' '<<(r[i]=x+1)<<endl;
      else cout<<i+1<<' '<<(r[i]=r[l[i]=i-a[i]])<<endl;
    } // 只需模拟上面的构造
    for(int i:l)cout<<i+1<<' ';
    cout<<endl;
  }
  return 0;
}
```

---

## 作者：I_am_Tangser (赞：0)

## 题外话

这题的左下角是 $(1,1)$，下面讲述中为了方便就改成左上角是 $(1,1)$。

## 题目大意

要求每列有一个房子，第 $i$ 个房子跟其他房子中的一个房子的曼哈顿距离为 $a_i$。

Medium 的性质是：$a_1=0$。

## 题目思路

既然性质是 $a_1=0$，那我们就从这方面入手，$a_1=0$，显然可以发现它只能跟自己配对，所以它放到哪里都是可以的，我们考虑将它放到 $(1,1)$。

然后考虑每个房子都跟在它纵坐标左边的房子配对，如果说第 $i$ 个房子的 $a_i\ge i$，那么说明它不能直接直线对上一个房子距离为 $a_i$，就只能对上 $a_1$，也就需要拐一个弯，它的坐标就是 $(i,a_i-i+2)$。如果 $a_i<i$ 它就可以直线对上一间房子，它的横坐标是第 $i-a_i$ 的横坐标，纵坐标是 $i$。

最后记得将 $(1,1)$ 从左上角转变成左下角。

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200010],b[200010],c[200010];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[i]=1;
	}
	cout<<"YES"<<endl<<"1 1"<<endl;
	b[1]=1;
	c[1]=1;
	for(int i=2;i<=n;i++){
		if(a[i]<i){
			cout<<i<<" "<<b[i-a[i]]<<endl;
			b[i]=b[i-a[i]];
			c[i]=i-a[i];
		}
		else{
			cout<<i<<" "<<2+a[i]-i<<endl;
			b[i]=2+a[i]-i;
			c[i]=1;
		}
	}
	for(int i=1;i<=n;i++)cout<<c[i]<<" ";
	return 0;
}
```

---

