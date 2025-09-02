# [NEERC 2014] Damage Assessment

## 题目描述

一个通过铁路运输汽油的罐车形状为两侧带有球形端盖的圆柱体。圆柱体的直径为 $d$，长度为 $l$。球形端盖的半径为 $r$（$2r \ge d$）。发生了铁路事故，罐车脱轨，现在躺在地上，部分储存的汽油已经流出。需要进行损失评估。通过测量圆柱体左侧和右侧底部点的高度差 $t$ 来确定罐车在地上的位置（$0 \le t \le l$）。通过测量圆柱体底部点和汽油顶部水平面的高度差 $h$ 来确定罐内汽油的水平面。为了解决这个问题，汽油的顶部水平面总是与罐车的圆柱部分相交（$0 \le h \le t + d \sqrt{1 - (t/l)^2}$）。

你的任务是计算罐车中剩余的汽油量。

![](/upload/images2/dmaage.png)

## 说明/提示

时间限制：1 秒，内存限制：256 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3000 6000 1600 0 3000
```

### 输出

```
50974.56
```

## 样例 #2

### 输入

```
3000 6000 1600 3441 4228
```

### 输出

```
40728.90
```

# 题解

## 作者：zhylj (赞：3)

考虑对每个平行于圆柱底面的截面，记其到圆柱底面的距离为 $x$，不妨求出截面上有油的面积 $f(x)$，然后使用自适应辛普森法求出 $\int_{-r}^{l+r} f(x)\mathrm dx$ 即为答案。

我们以截面上圆柱轴与截面的交点为原点，截面上过原点且平行于底面的直线为 $x$ 轴，过原点且垂直于 $x$ 轴的直线为 $y$ 轴建立坐标系，那么不难发现我们只需要求出截面所截得圆的半径以及水面与截面交线在坐标系中的高度即可求得截面上有油部分的面积，我们不妨分开讨论这两个问题：

对于水面与截面交线在坐标系中的高度 $Y$：

不妨考虑其与底面的高度 $Y + \dfrac d2$，那么有：
$$
\frac {Y + \frac d2}{h-x\cdot \frac tl} = \frac {l}{\sqrt {l^2-t^2}}\implies Y = \frac {h\cdot l-x\cdot t}{\sqrt {l^2-t^2}} - \frac d2
$$
![0018.PNG](https://s2.loli.net/2022/01/09/TlQLPXpWVJd5rZh.png)

对于所截得圆的半径 $R$，分两种情况讨论：

- $x\in [0,l]$，那么 $R = \dfrac d2$。

- 否则求出 $x$ 超出的部分的长度 $x'=-x$ 或 $x-l$（根据在左侧或者右侧），然后不难得到：

$$
R=\sqrt {r^2-\left(\sqrt {r^2 -\frac {d^2}4}+x'\right)^2}
$$

然后大力积分就做完了。 

```cpp
const ff EPS = 1e-8, INF = 1e5, PI = acos(-1);

ff d, l, r, t, h;

ff Sq(ff x) { return x * x; }

ff F(ff x) {
	ff l_d = sqrt(Sq(l) - Sq(t)) + EPS;
	ff Y = (h * l - t * x) / l_d - d / 2, R = 0;
	if(x > -EPS && x < l + EPS) R = d / 2;
	else {
		R = Sq(r) - Sq(sqrt(Sq(r) - Sq(d / 2)) + (x < EPS ? -x : x - l));
		if(R < 0) return 0;
		R = sqrt(R);
	}
	ff s_cir = Sq(R) * PI;
	if(Y > R - EPS) return s_cir;
	if(Y < -R + EPS) return 0;
	ff s = sqrt(Sq(R) - Sq(Y)) * Y,
		s_arc = acos(Y / R) * Sq(R);
	return s_cir - s_arc + s;
}

ff Simp(ff L, ff R) {
	return (R - L) * (F(L) + 4 * F((L + R) / 2) + F(R)) / 6;
}
ff Asr(ff L, ff R, ff ans, int step) {
	ff mid = (L + R) / 2, fl = Simp(L, mid), fr = Simp(mid, R);
	if(fabs(fl + fr - ans) < EPS && step < 0) return (fl + fr + ans) / 2;
	return Asr(L, mid, fl, step - 1) + Asr(mid, R, fr, step - 1);
}
ff Solve(ff L, ff R) {
	return Asr(L, R, Simp(L, R), 12);
}

int main() {
	rd(d, l, r, t, h);
	d /= 100; l /= 100; r /= 100; t /= 100; h /= 100;
	printf("%.2lf\n", Solve(-r, l + r));
	return 0;
}
```

---

