# Airport 机场

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4196

[PDF](https://uva.onlinejudge.org/external/14/p1450.pdf)

## 样例 #1

### 输入

```
3
1
1 1
3
3 2
0 3
2 0
6
0 1
1 1
1 2
1 1
1 1
6 0
```

### 输出

```
0
3
5```

# 题解

## 作者：Narcissusany (赞：3)

这题能比较自然地想到要二分。

但是问题在于二分了之后并不知道要怎么去 check。这个地方有个很妙的 idea。就是如果之前有机会要飞，可以不飞，等到什么时候攒到了 $mid$ 号再飞。这样就不需要再考虑这东西的后效性了。但是有一点需要注意，就是攒着一起飞的话，在第 $i$ 个时刻只能选择飞之前的，因为这个决策本质上等价于在 $i-1$ 时刻飞。所以也要分别统计 $W$ 和 $E$ 的可飞量。

```cpp
int T ;
int n ; 
int sum ;
int mus ;
int a[N] ; 
int b[N] ;

int main(){
	cin >> T ; 
	while (T --){
		cin >> n ; sum = mus = 0 ; 
		for (int i = 1 ; i <= n ; ++ i){
			a[i] = qr() ; b[i] = qr() ; 
			sum += a[i] ; mus += b[i] ;
		} 
		int ans = 0, mid ; 
		int l = 0, r = sum + mus ; 
		while (l <= r){ 
			bool chk_out = 1 ; 
			mid = (l + r) >> 1 ;
			int sa = 0, sb = 0 ;
			int ta = 0, tb = 0 ; 
			int x = mid + 1, t = 0 ; 
			for (int i = 1 ; i <= n ; ++ i){
				sa += a[i], sb += b[i] ; 
				int da = max(sa - x, 0) ; 
				int db = max(sb - x, 0) ;
				if (da > ta) fuck
				if (db > tb) fuck
				if (da + db > t) fuck 
				if (sa > ta) ++ ta ; 
				if (sb > tb) ++ tb ; 
				if (sa + sb > t) ++ t ; 
			}
			if (chk_out)
				ans = mid, r = mid - 1 ; 
			else l = mid + 1 ;
		}
		cout << ans << '\n' ; 
	}
}
```

---

