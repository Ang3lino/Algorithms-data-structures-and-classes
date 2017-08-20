
import java.util.*;
import java.math.*;

public class SquareRoot
{
	private static Map <Integer, BigInteger> doubleFact = 
		new HashMap <Integer, BigInteger> (); 
	private static Map <Integer, BigInteger> fact = 
		new HashMap <Integer, BigInteger> (); 

	// NO puedes hacer que el indice sea no entero, long no funciona
	static BigInteger factorial (final int n) {
		if (fact.containsKey (n))
			return fact.get(n);
		BigInteger value = new BigInteger ("1");
		if (n == 0)
			value = BigInteger.ONE;
		else 
			value = factorial (n - 1).multiply (BigInteger.valueOf (n));
		fact.put (n, value);
		return value;
	}

	static BigInteger doubleFactorial (final int n) {
		if (doubleFact.containsKey (n))
			return doubleFact.get (n);
		BigInteger value = new BigInteger ("1");
		if (n <= 1)
			value = BigInteger.ONE; 
		else 
			value = doubleFactorial (n - 2).multiply (BigInteger.valueOf (n));
		doubleFact.put (n, value);
		return value;
	}

	static BigRational squareRootOfTwo () {
		BigRational sum = new BigRational ();
		BigRational frac2 = new BigRational();
		// 62 max
		for (int k = 1; k <= 63; k++) {
			frac2.setNumerator (doubleFactorial (2 * k - 3).multiply (
						BigInteger.valueOf ((long) Math.pow (-1, k + 1))));
			frac2.setDenominator (factorial (k));
			frac2.setDenominator (frac2.getDenominator().multiply (
						BigInteger.valueOf ((long) Math.pow (2, k))));
			sum = BigRational.add (sum, frac2);
		}
		frac2.setNumerator (BigInteger.ONE); 
		frac2.setDenominator (BigInteger.ONE);
		sum = BigRational.add (frac2, sum);
		return sum; 
	}

	public static void main(String[] args) {
		BigRational z = new BigRational ();
		z = squareRootOfTwo();
		System.out.println(z.getNumerator());
		System.out.println(z.getDenominator());
	}
}

