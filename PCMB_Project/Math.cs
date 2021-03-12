using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace ManagedSeverForInterop
{
    public interface IMath
    {
         int MultiplicationValue { get; set; }
         int DivisionValue { get; set; }
         int MultiplicationOfTwoIntegers(int num1, int num2);
         int DivisionOfTwoIntegers(int num1, int num2);
    }
	[ClassInterface(ClassInterfaceType.AutoDispatch)]
	public class  Math:IMath
	{
		public int MultiplicationValue { get; set; }
		public int DivisionValue { get; set; }
		public Math()
		{

		}

		public int MultiplicationOfTwoIntegers(int num1,int num2)
		{
			MultiplicationValue=num1 *num2;
			MessageBox.Show("Multiplication of 2 integers: "+MultiplicationValue);
			return MultiplicationValue;
		}

		public int DivisionOfTwoIntegers(int num1,int num2)
		{
			DivisionValue=num1 / num2;
			MessageBox.Show("Division of 2 Integers: "+DivisionValue);
			return DivisionValue;
		}
	}
}