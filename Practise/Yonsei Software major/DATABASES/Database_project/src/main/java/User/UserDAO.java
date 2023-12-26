package User;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet; // 단축키 : ctrl + shift + 'o'

public class UserDAO {
	private Connection conn; //db 접근 객체 
	private PreparedStatement pstmt;
	private ResultSet rs; // db 결과를 담는 객체
	
	public UserDAO() { // dao 생성자에서 db connection 
		try {
			String dbURL = "jdbc:mariadb://localhost:3306/drugbank";
			String dbID = "root"; //계정
			String dbPassword = "sw701020"; //비밀번호
			Class.forName("org.mariadb.jdbc.Driver");
			conn = DriverManager.getConnection(dbURL, dbID, dbPassword);
		}catch(Exception e) {
			e.printStackTrace();
		}
	}
	// 로그인 기능 
	public int login(String email, String password) {
		String SQL = "SELECT Password FROM generaluser WHERE Email = ?";
		try {
			pstmt = conn.prepareStatement(SQL);
			pstmt.setString(1, email); //sql Injection 공격 방어 수단 : 1번째 물음표에 email 입력
			rs = pstmt.executeQuery(); // 쿼리 실행 
			if (rs.next()) {
				if (rs.getString(1).equals(password)) // rs.getString(1) : select된 첫번째 컬럼
					return 1; //로그인 성공
				else
					return 0; // 비밀번호 틀림
			}
			return -1; // 아이디 없음 
		}catch(Exception e) {
			e.printStackTrace();
			
		}
		return -2; //DB 오류 
	}
	public int join(User user) {
		String SQL = "INSERT INTO Generaluser (username, email, password, address, phonenumber) VALUES (?, ?, ?, ?, ?)";
		try {
            pstmt = conn.prepareStatement(SQL);
            pstmt.setString(1, user.getusername());
            pstmt.setString(2, user.getemail());
            pstmt.setString(3, user.getpassword());
            pstmt.setString(4, user.getaddress());
            pstmt.setString(5, user.getphonenumber());		
			return pstmt.executeUpdate(); // 0이상 값이 return된 경우 성공 
		}catch(Exception e) {
			e.printStackTrace();
			
		}
		return -1; //DB 오류 
	}
}