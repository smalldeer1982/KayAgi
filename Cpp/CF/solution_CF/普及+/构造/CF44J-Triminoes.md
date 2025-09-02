# Triminoes

## 题目描述

给出一个$n \times m$的棋盘，棋盘用黑白两色染色（染色规则与国际象棋棋盘相同），其上某些格子被挖掉了，问能否使用$1 \times 3$和$3 \times 1$的矩形不重不漏地覆盖没有挖空的棋盘部分。

注意：矩形放置的中间的格子必须要是黑色

## 样例 #1

### 输入

```
6 10
.w.wbw.wbw
wbwbw.w.w.
bw.wbwbwbw
w.wbw.wbwb
...wbw.w.w
..wbw.wbw.
```

### 输出

```
YES
.a.aaa.ccc
baccc.c.a.
ba.dddcbab
b.aaa.cbab
...bbb.b.b
..ccc.ddd.```

## 样例 #2

### 输入

```
2 2
wb
bw
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
1 3
wbw
```

### 输出

```
YES
bbb
```

## 样例 #4

### 输入

```
1 3
...
```

### 输出

```
YES
...
```

# 题解

## 作者：有趣的问题 (赞：1)

翻译很清晰，题意就不赘述了。

### 解题思路

这题很关键的一点，就是要抓住**放置在中间的格子必须是黑色**这一要求。

考虑从左到右，从上到下一次遍历每一个点。

对于遍历到的最左上的，没被挖掉的，还没有放置骨牌的点，如果它是黑色，那我们无论如何都不可能满足题意了，直接判无解。如果它是白色的，那么就有横着放和竖着放两种放法。如果能横着放的话，我们一定选择横着放，否则它右边那个白色的位置就没有骨牌能覆盖到了。所以这题直接贪心放就可以了。

另外要求相邻的骨牌字母不同，我们只用比较一个骨牌四周的颜色就可以了。根据著名的四色定理，用四个字母是足够输出了~~（有兴趣的话可以自己证明一下）~~。

### 丑陋的代码

因为实在是太丑了，放一下solve函数：

```
bool solve(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(tu[i][j]=='.')continue;
			if(used[i][j])continue;
			if(tu[i][j]=='b')return 0;
			if(tu[i][j+1]=='b'&&!used[i][j+1]){
				if(tu[i][j+2]!='w'||used[i][j+2])return 0;
				used[i][j+1]=used[i][j+2]=1;
				cl[i][j]='a';
				int x=i,y=j;
				for(int k=1;k<=3;k++){
					if(cl[x][y-1]==cl[x][y])cl[x][y]++;
					if(cl[x-1][y]==cl[x][y])cl[x][y]++;
					if(cl[x-1][y+1]==cl[x][y])cl[x][y]++;
					if(cl[x-1][y+2]==cl[x][y])cl[x][y]++;
					if(cl[x][y+3]==cl[x][y])cl[x][y]++;
					if(cl[x+1][y]==cl[x][y])cl[x][y]++;
					if(cl[x+1][y+1]==cl[x][y])cl[x][y]++;
					if(cl[x+1][y+2]==cl[x][y])cl[x][y]++;
				}
				cl[x][y+1]=cl[x][y+2]=cl[x][y];
			}
			else{
				if(tu[i+1][j]!='b'||used[i+1][j]||tu[i+2][j]!='w'||used[i+2][j])return 0;
				used[i+1][j]=used[i+2][j]=1;
				int x=i,y=j;
				cl[x][y]='a';
				for(int i=1;i<=3;i++){
					if(cl[x][y-1]==cl[x][y])cl[x][y]++;
					if(cl[x-1][y]==cl[x][y])cl[x][y]++;
					if(cl[x+1][y-1]==cl[x][y])cl[x][y]++;
					if(cl[x+2][y-1]==cl[x][y])cl[x][y]++;	
					if(cl[x][y+1]==cl[x][y])cl[x][y]++;
					if(cl[x+3][y]==cl[x][y])cl[x][y]++;
					if(cl[x+1][y+1]==cl[x][y])cl[x][y]++;
					if(cl[x+2][y+1]==cl[x][y])cl[x][y]++;
				}
				cl[x+1][y]=cl[x+2][y]=cl[x][y];
			}
		}
	}
	return 1;
}
```



---

