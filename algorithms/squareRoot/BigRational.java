
import java.util.*;
import java.math.*;

public class BigRational {
	private BigInteger num, den; 

	public BigRational () {
		num = BigInteger.ZERO;
		den = BigInteger.ONE;
	}

	public BigRational (BigInteger num, BigInteger den) {
		if (den.compareTo(BigInteger.ZERO) == 0)
			throw new RuntimeException ("Indeterminacion del tipo x / 0");
		this.num = num;
		this.den = den;
		simplify ();
	}

	private void simplify () {
		BigInteger mxd = num.gcd (den);
		num = num.divide(mxd);
		den = den.divide(mxd);
	}

	public void add (BigRational fraction) {
		num = num.multiply (fraction.den).add (fraction.num.multiply (den));
		den = den.multiply (fraction.den);
		simplify ();
	}

	public static BigRational add (BigRational x, BigRational y) {
		return new BigRational (x.num.multiply (y.den).add (x.den.multiply (y.num)), 
								x.den.multiply (y.den));
	}

	public BigInteger getNumerator () {
		return num; 
	} 

	public BigInteger getDenominator () {
		return den;
	}

	public void setNumerator (BigInteger _num) {
		num = _num;
		simplify ();
	}

	public void setDenominator (BigInteger _den) {
		if (_den.compareTo (BigInteger.ZERO) == 0)
			throw new RuntimeException ("Se esta tratando de establecer al " +
				"denominador en 0");
		den = _den;
		simplify ();
	}

}
