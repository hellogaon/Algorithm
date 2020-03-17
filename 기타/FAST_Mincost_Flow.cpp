// Fast MinCostFlow
// 주의) 그래프 연결 시, 1~based 사용.
// https://github.com/hongjun7/Competitive-Programming/blob/master/Library/C%2B%2B/Graph/FAST%20Mincost%20Flow.cpp
const int MAXV = 2505;
const int MAXE = 100005;
const int S = MAXV-2;
const int E = MAXV-1;
//variable 'ending' determines maxflow or not.
struct MinCostFlow{
	int sz, n, ending;
	int st, en, maxflow, mincost;
	bool vis[MAXV];
	int net[MAXV], pre[MAXV], cur[MAXV], dis[MAXV], Q[100 * MAXV], fr, re;
	
  MinCostFlow(int v){
		ending = 0;
		n = v, sz = 0;
		memset(net, -1, sizeof(net));
	}

  struct Edge{
		int v, cap, cost, next;
		Edge() {}
		Edge(int a, int b, int c, int d){
			v = a, cap = b, cost = c, next = d;
		}
	} E[MAXE];
	
	void addEdge(int u, int v, int cap, int cost){
		E[sz] = Edge(v, cap, cost, net[u]);
		net[u] = sz++;
		E[sz] = Edge(u, 0, -cost, net[v]);
		net[v] = sz++;
	}
	
  bool adjust(){
		int v, min = INF;
		for(int i=0;i<=n;i++){
			if(!vis[i]) continue;
			for(int j=net[i];v=E[j].v,j!=-1;j=E[j].next)
				if(E[j].cap && !vis[v] && dis[v] - dis[i] + E[j].cost < min)
					min = dis[v] - dis[i] + E[j].cost;
		}
		if(min == INF) return false;
		for(int i=0;i<=n;i++)
      if(vis[i]) cur[i] = net[i], vis[i] = false, dis[i] += min;
		return true;
	}

	int augment(int i, int flow){
		if(i == en){
			if(dis[st] < 0) mincost += dis[st] * flow;
			else ending = 1; //mcf, not mcmf
			maxflow += flow;
			return flow;
		}
		vis[i] = true;
		for(int j=cur[i],v;v=E[j].v,j!=-1;j=E[j].next){
			if(!E[j].cap) continue;
			if(vis[v] || dis[v] + E[j].cost != dis[i]) continue;
			int delta = augment(v, std::min(flow, E[j].cap));
			if(delta){
				E[j].cap -= delta;
				E[j ^ 1].cap += delta;
				cur[i] = j;
				return delta;
			}
		}
		return 0;
	}

	void spfa(){
		int u, v;
		for(int i=0;i<=n;i++) vis[i] = false, dis[i] = INF;
		dis[st] = 0;
		Q[fr = re = 0] = st;
		vis[st] = true;
		while(fr <= re){
			u = Q[fr++];
			vis[u] = false;
			for(int i=net[u];v=E[i].v,i!=-1;i=E[i].next){
				if(!E[i].cap || dis[v] <= dis[u] + E[i].cost) continue;
				dis[v] = dis[u] + E[i].cost;
				if(!vis[v]){
					vis[v] = true;
					Q[++re] = v;
					if(dis[Q[fr]] > dis[Q[re]]) swap(Q[fr], Q[re]);
				}
			}
		}
		for(int i=0;i<=n;i++) dis[i] = dis[en] - dis[i];
	}

	int solve(int s, int t){
		st = s, en = t;
		spfa();
		mincost = maxflow = 0;
		for(int i=0;i<=n;i++) vis[i] = false, cur[i] = net[i];
		do{
			while(augment(st, INF)){
				if(ending) return mincost;  //mcf, not mcmf
				memset(vis, false, sizeof(vis));
			}
		}while(adjust());
		return mincost;
	}
};