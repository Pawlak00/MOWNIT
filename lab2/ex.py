        sem_val=list(self.SEM.values())[0]
        SEM_edge=list(self.SEM.keys())[0]
        SEM_edge_rev=(SEM_edge[1],SEM_edge[0])
        Resistance={(u,v):self.Resistance[(u,v)] for (u,v) list(in self.Resistance.keys())}
        Resistance[(SEM_edge[0],self.N)]=0
        Resistance[(self.N,SEM_edge[1])]=self.Resistance[SEM_edge if SEM_edge in self.Resistance else SEM_edge_rev]
        SEM={(SEM_edge[0],self.N):sem_val}
        Resistance.pop(SEM_edge if SEM_edge in self.Resistance else SEM_edge_rev)
        components = [(u,v,self.Resistance[(u,v)]) for u,v in self.Resistance]
        u_s=list(self.SEM.keys())[0][0]
        v_s=list(self.SEM.keys())[0][1]
        w_s=self.SEM[(u_s,v_s)]
        components.append((u_s,v_s,w_s))
        g2Count = 1
        matrixSize = self.N + 1
        A = np.zeros((matrixSize, matrixSize))
        b = np.zeros(matrixSize)
        g2Index = matrixSize - g2Count
        for i,component in enumerate(components):
            high = component[0]
            low = component[1]
            value = component[2]
            if i!=len(components)-1:
                if high != 0:
                    A[high - 1][high - 1] = A[high - 1][high - 1] + (1/value if value!=0 else 0)
                if low != 0:
                    A[low - 1][low - 1] = A[low - 1][low - 1] + (1/value if value!=0 else 0)
                if high != 0 and low != 0:
                    A[high - 1][low - 1] = A[high - 1][low - 1] - (1/value if value!=0 else 0)
                    A[low - 1][high - 1] = A[low - 1][high - 1] - (1/value if value!=0 else 0)
            else:
                if high != 0:
                    A[high - 1][g2Index] = A[high - 1][g2Index] + 1
                    A[g2Index][high - 1] = A[g2Index][high - 1] + 1
                if low != 0:
                    A[low - 1][g2Index] = A[low - 1][g2Index] - 1
                    A[g2Index][low - 1] = A[g2Index][low - 1] - 1
                b[g2Index] = value
                g2Index = g2Index + 1
        sol={}
        x=np.array(0)
        x=np.append(x,np.linalg.solve(A, b))
        for (u,v) in Resistance:
            r=Resistance[(u,v)]
            if r!=0 and u!=self.N and v!=self.N:
                if x[u]>x[v]:
                    sol[(u,v)]=(x[u]-x[v])/r
                else:
                    sol[(v,u)]=(x[v]-x[u])/r
        SEM_edge=SEM_edge if x[self.N]>x[SEM_edge[1]] else (SEM_edge[1],SEM_edge[0])
        sol[SEM_edge]=x[self.N]-x[SEM_edge[0]] if x[self.N]>x[SEM_edge[0]] else x[SEM_edge[0]]-x[self.N] 
        return sol