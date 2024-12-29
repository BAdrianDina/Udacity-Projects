


function ConstructCayleyGraph(p, q)
	/***********************************
	 * Author: Bogdan Adrian Dina
	 * Input: primes p, q, st, p,q cong 1 (mod 4)
	 * Output: 
	 * 
	 * Explanations: 
	 * Example: 
	/***********************************/
	
	assert (p mod 4) eq 1; 
	assert (q mod 4) eq 1;
	
	q_residue := LegendreSymbol(p,q);
	
	if q_residue eq 1 then
		G, iSet := PSL(2, q);
	else
		G, iSet := PGL(2, q);
	end if;
	
return G, iSet;
end function;



G, iSet := ConstructCayleyGraph(5, 13);
