import static org.junit.Assert.*;

import org.junit.Test;

public class UrlValidatorTestCorrect {

	@Test
	public void schemeTest_Null() {
		UrlValidator urlTest = new UrlValidator();	
		String testStr = "www.oregonstate.edu";
		assertFalse(urlTest.isValid(testStr));		
	}

	@Test
	public void schemeTest_http() {
		UrlValidator urlTest = new UrlValidator();	
		String testStr = "http://www.oregonstate.edu";
		assertTrue(urlTest.isValid(testStr));		
	}	 

	@Test
	public void schemeTest_HTTPS() {
		UrlValidator urlTest = new UrlValidator();	
		String testStr = "HTTPS://www.oregonstate.edu";
		assertTrue(urlTest.isValid(testStr));		
	}
	
	@Test
	public void schemeTest_fTp() {
		UrlValidator urlTest = new UrlValidator();	
		String testStr = "fTp://www.oregonstate.edu";
		assertTrue(urlTest.isValid(testStr));	
	}	
	

	@Test
	public void schemeTest_0123() {
		UrlValidator urlTest = new UrlValidator();	
		String testStr = "0123://www.oregonstate.edu";
		assertFalse(urlTest.isValid(testStr));		
	}
	
	@Test
	public void schemeTest_abc() {
		UrlValidator urlTest = new UrlValidator();	
		String testStr = "abc://www.oregonstate.edu";
		assertFalse(urlTest.isValid(testStr));		
	}
	
	@Test
	public void schemeTest_ABC() {
		UrlValidator urlTest = new UrlValidator();	
		String testStr = "ABC://www.oregonstate.edu";
		assertFalse(urlTest.isValid(testStr));		
	}
	
	@Test
	public void schemeTest_0123_schemes() {
		String[] schemes = {"0123"};
		UrlValidator urlTest = new UrlValidator(schemes);	
		String testStr = "0123://www.oregonstate.edu";
		assertFalse(urlTest.isValid(testStr));		
	}	
	
	@Test
	public void schemeTest_abc_schemes() {
		String[] schemes = {"abc"};
		UrlValidator urlTest = new UrlValidator(schemes);
		String testStr = "abc://www.oregonstate.edu";
		assertTrue(urlTest.isValid(testStr));		
	}
	
	@Test
	public void schemeTest_ABC_schemes() {
		String[] schemes = {"ABC"};
		UrlValidator urlTest = new UrlValidator(schemes);	
		String testStr = "ABC://www.oregonstate.edu";
		assertTrue(urlTest.isValid(testStr));		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}	