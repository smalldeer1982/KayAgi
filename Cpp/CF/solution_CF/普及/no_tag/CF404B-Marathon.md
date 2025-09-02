# Marathon

## 题目描述

Valera takes part in the Berland Marathon. The marathon race starts at the stadium that can be represented on the plane as a square whose lower left corner is located at point with coordinates $ (0,0) $ and the length of the side equals $ a $ meters. The sides of the square are parallel to coordinate axes.

As the length of the marathon race is very long, Valera needs to have extra drink during the race. The coach gives Valera a bottle of drink each $ d $ meters of the path. We know that Valera starts at the point with coordinates $ (0,0) $ and runs counter-clockwise. That is, when Valera covers $ a $ meters, he reaches the point with coordinates $ (a,0) $ . We also know that the length of the marathon race equals $ nd+0.5 $ meters.

Help Valera's coach determine where he should be located to help Valera. Specifically, determine the coordinates of Valera's positions when he covers $ d,2·d,...,n·d $ meters.

## 样例 #1

### 输入

```
2 5
2
```

### 输出

```
1.0000000000 2.0000000000
2.0000000000 0.0000000000
```

## 样例 #2

### 输入

```
4.147 2.8819
6
```

### 输出

```
2.8819000000 0.0000000000
4.1470000000 1.6168000000
3.7953000000 4.1470000000
0.9134000000 4.1470000000
0.0000000000 2.1785000000
0.7034000000 0.0000000000
```

# 题解

## 作者：aeiouaoeiu (赞：0)

设 $l$ 为走到了所处的边的哪个位置（从碰到所处的边时所经过的点到现在所处点的距离），则每一次 $l\rightarrow l+d$，如果 $l>a$ 就换方向，一共会换 $\lfloor{\dfrac{l}{a}}\rfloor$ 次方向，此时 $l\rightarrow l-a\lfloor{\dfrac{l}{a}}\rfloor$，最后根据方向和 $l$ 判断位置即可。

```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define pb push_back 
using namespace std;
typedef long long ll;
typedef long double db;
const int maxn=100005;
ll pos;
double a,d,n,l;
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	ll T=1;
	//cin>>T;
	for(int tcs=1;tcs<=T;tcs++){
		cin>>a>>d>>n;
		cout<<fixed<<setprecision(10);
		for(int i=1;i<=n;i++){
			l+=d;
			if(l>a) pos=(pos+(ll)(l/a))%4,l-=(ll)(l/a)*a;
			if(pos==0) cout<<l<<" "<<0.0<<"\n";
			if(pos==1) cout<<a<<" "<<l<<"\n";
			if(pos==2) cout<<a-l<<" "<<a<<"\n";
			if(pos==3) cout<<0.0<<" "<<a-l<<"\n";
		}
	}
	return 0;
}
```

---

