

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.ArrayList;

class Table {

	// attributes for Table class
	String symbol;
	int address;
	int index;

	public Table(String symbol, int address) {
		
		this.symbol = symbol;
		this.address = address;

	}

	public Table(String symbol, int address, int index) {
		

		this.symbol = symbol;
		this.address = address;
		this.index = index;

	}

	// for getting the address of given value
	public int getAddress() {
		return address;
	}

}

public class PassTwo {
	ArrayList<Table> SymTab, LitTab;

	
	public PassTwo() {
		SymTab = new ArrayList<>();          // for symbol table
		LitTab = new ArrayList<>();          // for literal table
	}

	public void takeTables()       // for reading the tables
	{
		BufferedReader BR = null;

		String currentLine;        // for current line
		try {
			FileReader FR = new FileReader("SymTab.txt");   // filereader for symtab
			BR = new BufferedReader(FR);

			while ((currentLine = BR.readLine()) != null) {

				// split string into strings of array with separator as space or multiple space
				String parts[] = currentLine.split("\\s+");

				// symbol,address and index adding into symTab
				SymTab.add(new Table(parts[1], Integer.parseInt(parts[2]), Integer.parseInt(parts[0])));
			}

			BR.close();

			FileReader FR2 = new FileReader("LitTab.txt");  // filereader for littab
			BR = new BufferedReader(FR2);

			while ((currentLine = BR.readLine()) != null) {
				// spliting
				String parts[] = currentLine.split("\\s+");

				// adding in litTab
				//LitTab.add(new Table(parts[1], Integer.parseInt(parts[2]), Integer.parseInt(parts[0])));
				LitTab.add(new Table(parts[0], Integer.parseInt(parts[2])));
			}

			BR.close();
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}
	}

	// for creating machine code
	public void createCode(String filename) throws Exception {
		takeTables();

		// for reading IC file
		FileReader FR3 = new FileReader(filename);
		BufferedReader br = new BufferedReader(FR3);

		// for writing in file
		FileWriter FW = new FileWriter("Machinecode.txt");
		BufferedWriter bw = new BufferedWriter(FW);

		String currentLine; // for reading line by line
		String code;
		

		while ((currentLine = br.readLine()) != null) {

			// spliting by spaces
			String tokens[] = currentLine.split("\\s+");

			// tokenizing and checking
			//ignore AD and DL,02
			if (tokens[0].contains("AD") || tokens[0].contains("DL,02")) {
				bw.write("\n");
				continue;
			}
			// checking for one operands
			else if (tokens.length == 2) {
				if (tokens[0].contains("DL")) {

					// replacing all non digits with empty character
					tokens[0] = tokens[0].replaceAll("[^0-9]", "");

					// checking for DC
					if (Integer.parseInt(tokens[0]) == 1) {

						// taking the value of constant
						int c = Integer.parseInt(tokens[1].replaceAll("[^0-9]", ""));
						code = "00\t0\t" + String.format("%03d", c) + "\n";
						bw.write(code);

					}
				}
				// checking for IS
				else if (tokens[0].contains("IS")) {

					// taking the opcode
					int opcode = Integer.parseInt(tokens[0].replaceAll("[^0-9]", ""));

					// if there is symbol
					if (tokens[1].contains("S")) {

						// taking the index of symbol
						int symIndex = Integer.parseInt(tokens[1].replaceAll("[^0-9]", ""));

						// taking the address of symbol from symtab
						code = String.format("%02d", opcode) + "\t0\t"
								+ String.format("%03d", SymTab.get(symIndex - 1).getAddress()) + "\n";
						bw.write(code);
					}

					// if there is literal
					else if (tokens[1].contains("L")) {
						int symIndex = Integer.parseInt(tokens[1].replaceAll("[^0-9]", ""));
						code = String.format("%02d", opcode) + "\t0\t"
								+ String.format("%03d", LitTab.get(symIndex - 1).getAddress()) + "\n";
						bw.write(code);
					}

				}
			}

			 //if no registers
			else if (tokens.length == 1 && tokens[0].contains("IS")) {
				int opcode = Integer.parseInt(tokens[0].replaceAll("[^0-9]", ""));
				code = String.format("%02d", opcode) + "\t0\t" + String.format("%03d", 0) + "\n";
				bw.write(code);
			}

			// checking for two operands
			else if (tokens[0].contains("IS") && tokens.length == 3) {

				// taking opcode
				int ocode = Integer.parseInt(tokens[0].replaceAll("[^0-9]", ""));

				// taking register code
				int rcode = Integer.parseInt(tokens[1]);

				// if there is symbol
				if (tokens[2].contains("S")) {
					int symIndex = Integer.parseInt(tokens[2].replaceAll("[^0-9]", ""));
					code = String.format("%02d", ocode) + "\t" + rcode + "\t"
							+ String.format("%03d", SymTab.get(symIndex - 1).getAddress()) + "\n";
					bw.write(code);
				}

				// if there is literal
				else if (tokens[2].contains("L")) {
					int symIndex = Integer.parseInt(tokens[2].replaceAll("[^0-9]", ""));
					code = String.format("%02d", ocode) + "\t" + rcode + "\t"
							+ String.format("%03d", LitTab.get(symIndex - 1).getAddress()) + "\n";
					bw.write(code);
				}
			}

		}
		bw.close();
		br.close();

	}

	public static void main(String[] args) {
		PassTwo pass2 = new PassTwo();

		try {
			pass2.createCode("test.txt");
		} catch (Exception e) {
			e.printStackTrace();
		}
	};

}