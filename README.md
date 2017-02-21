# Handling Compare Tool
###### _Version 1.0_

## Intro

This is a tool that lets you observe Grand Theft Auto V's handling files in a couple of different ways.

The main features include:

  * The ability to automatically find differences between two handling files
  * Filter the data by either vehicle name, or the name of a data field
  * Export all the differences between two handling files
  * Export any data fields of your choice
  * Give you a textual breakdown of the handling flags, model flags and damage flags of a vehicle

## Download

**You can download the binary release here:**

  * [Windows, 32-bit](https://raw.githubusercontent.com/adam10603/HandlingCompareTool/master/bin/HandlingCompareTool_x86.zip)
  * [Windows, 64-bit](https://raw.githubusercontent.com/adam10603/HandlingCompareTool/master/bin/HandlingCompareTool_x64.zip)

## Usage

Using the tool is pretty self-explanatory. You can open up handling files as **either File "A", File "B", or one in both slots (in order to compare them)**.

After opening a file, the label below the associated "Open File" button will indicate if everything went fine, or not.

If everything's fine, you will see all the data displayed in the table. From here, you can further **filter the data by entering a vehicle name and/or the name of a data field** and pressing the "Search" button (the text boxes have autocomplete as well to make this easier).

For the `strHandlingFlags`, `strModelFlags` and `strDamageFlags` fields, the tool can give you a **list of the flags** encoded in the hexadecimal value when you **hover over the names of these data fields with the mouse** (where it says `strHandlingFlags` for example).

If you opened two different handling files, the **"Only Show Fields With Differences"** checkbox will come alive, which will do exactly as it says: it will only show the lines where there are differences between the files.

After finding what you need, you can export the data in various ways. You can either **export all the differences between the files** automatically, **or export any lines that you selected** by ticking their checkboxes in the table.

In either case you will be presented with the **option to have the data fields in rows, or in columns**. Choose whichever format your heart desires here.

The format of these exports is something called a **tab separated file**. This means that each value on a new column will be separeted from the previous one with a tab character. This makes it very **easy to copy-paste the results into a spreadsheet**, since any hald-decent spreadsheet application will automatically recognize the columns when data in this format is pasted into a table.

Btw, **you can export the selected data fields even if there's only one file open**, which means you can use this as just a conversion tool to make it easier to import handling data into a spreadsheet, if that's your thing by any chance :)

### Files

**The tool supports both the old-gen `handling.dat` and the new-gen `handling.meta` formats**, and all the features work with either of them seamlessly, which means **you can even compare old-gen and new-gen files directly**.

**IMPORTANT:** The tool will assume the file's format based on the file extension, so make sure your files correctly end in `.dat` or `.meta`.

I thought about including some handling files with the tool to get people started, but I decided not to redistribute the game files, so you will have to source those yourself.

## Notes

If you find any bugs, or have any suggestions, feel free to tweet at me or something (same user name as here).

Regarding the source code:
This is a Visual Studio 2017 project, utilizing some C++ 17 features, so you will need the latest RC of Visual Studio 2017 if you want to compile it yourself.

## Version history:

* v1.0:
  * Initial release

================
Licensed under WTFPL v2 (see the file `COPYING`)

_Note: Although this legally lets you do anything, but if you get rid of my watermark, I will officially not like you._
