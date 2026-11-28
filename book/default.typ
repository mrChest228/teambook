#let margin = (x: 4.5mm, y: 4.5mm) // The printer prints from 4.5mm to the edges
#let gutter = 3.5mm
#let cols-cnt = 3
// Font sizes: headings of 3 levels and numbers at their start, main text, code
#let font-sizes = (h1: 17pt, h2: 13pt, h3: 9.5pt, num1: 12pt, num2: 10pt, num3: 7.5pt, text: 7pt, code: 7pt, math-block: 9pt)
// Code blocks: the cell of 7pt with -0.12pt tracking. Typst drops tracking at every colour/weight change, so columns drifted
#let code-size = font-sizes.code * 0.9714
// Inline formula is this times bigger than the text around it: its small variables (x, n) are as high as small letters of Georgia
#let math-inline-scale = 1.08
// Background of the inline code and of every second line of the code block
#let code-fill = rgb("#EEEEEE")

#import "@preview/codly:2.0.0" as codly
// Border of line numbers and the cpp label
#let code-stroke = 0.8pt + rgb("#777777")
#let frame-stroke = 1pt + rgb("#AAAAAA")
#let badge-shift = (x: -1.2pt, y: 1.9pt) // Label of the language from the top right corner of the code
#let code-radius = 3pt

// Bold l/ll in long double functions, long rounding functions and __builtin_*ll
#let comment-gap = 2pt
// $...$ in a comment is a Typst formula drawn with the comment font
#let comment-math(s) = {
  show math.equation: set text(font: ("Caveat", "New Computer Modern Math"), size: 9.5pt)
  math.equation(math.upright(eval(s, mode: "math")))
}
// The // comment of a line of code: from the first // outside of string and char literals to the end
#let comment-of(line) = {
  let (quote, esc, prev, at) = (none, false, none, 0)
  for c in line.clusters() {
    if quote != none {
      if esc { esc = false } else if c == "\\" { esc = true } else if c == quote { quote = none }
    } else if c == "\"" or c == "'" { quote = c } else if c == "/" and prev == "/" { return line.slice(at - 1) }
    prev = c
    at += c.len()
  }
  none
}
#let bold-l(body, size: font-sizes.code) = {
  show "_": set text(baseline: -0.2em) // Courier New: from under the line to the bottom of o
  // Courier New glyph fixes: a dot in the centre of 0, * centred at + and -, punctuation centred in its cell.
  // Sizes are absolute: the raw rule sets the size of every text with show text, it would override sizes in em
  let bold() = text.weight == "bold"
  let comment() = text.fill == rgb("#505050") // Caveat
  show "0": it => context {
    if comment() { return it }
    let (y, d) = if bold() { (0.3167, 0.15) } else { (0.3064, 0.12) } // em: centre of the ink of 0, diameter of the dot
    // An empty box sits on the baseline, so the dot does not take part in the line: no box around 0 in codly
    box(place(bottom + left, dx: (0.3 - d / 2) * size, dy: -(y - d / 2) * size,
      circle(radius: d / 2 * size, fill: text.fill, stroke: none))) + it
  }
  show "*": it => context text(baseline: if bold() { 0.138em } else { 0.149em }, it)
  let shifts = ( // em: ink centre to cell centre, (regular, bold). Other ASCII symbols are centred in Courier New
    ",": (0.051, 0), ";": (0.0364, 0), "(": (-0.0779, -0.0764), ")": (0.0706, 0.0696),
    "[": (-0.0637, -0.0627), "]": (0.0618, 0.0627), "<": (0.0122, 0.0264), ">": (-0.0122, -0.0273),
  )
  show regex("[,;()\\[\\]<>]"): it => context {
    if comment() { return it }
    let dx = shifts.at(it.text).at(if bold() { 1 } else { 0 }) * size
    h(dx) + it + h(-dx)
  }
  show regex("\\b(__builtin_\\w+ll|(sqrt|cbrt|fabs|pow|exp|log|log2|log10|sin|cos|tan|asin|acos|atan|atan2|hypot|floor|ceil|round|fmod)l|ll?(round|rint))\\b"): it => {
    let t = it.text
    let prefixed = t == "lround" or t == "llround" or t == "lrint" or t == "llrint"
    let k = if t.starts-with("__builtin") { 2 } else { 1 }
    if prefixed {
      let k = if t.starts-with("ll") { 2 } else { 1 }
      [#strong(t.slice(0, k))#t.slice(k)]
    } else {
      [#t.slice(0, t.len() - k)#strong(t.slice(t.len() - k))]
    }
  }
  // Caveat letters stick out to the right of their width: every comment word ends comment-gap before the edge.
  // In the middle the space is narrower by the gap, at a line break the space vanishes and the gap stays
  // code-file ends lines with a comment with a space, so the gap is also after the last word
  show text.where(fill: rgb("#505050")): it => {
    show " ": h(comment-gap) + text(font: "Caveat", size: 9.5pt, fill: black, spacing: 100% - comment-gap, " ")
    show regex("\\$[^$]+\\$"): m => comment-math(m.text.slice(1, -1))
    it
  }
  body
}

// Border of a code block: the sides are on every part, the top and the bottom with round corners only at the
// real start and end of the block, so an unfinished part is open. The fills of the first and the last line go
// on to the border
#let code-cap(at-top, y: top, separator-x: none, gutter-fill: none, code-paint: none) = {
  let r = code-radius
  let w = frame-stroke.thickness
  let s = 0.6pt + w // Covers the square corner of the sides and of the fill
  let k = 0.5523 // Control points of a cubic curve that is a quarter of a circle
  let sy = if at-top { 1 } else { -1 }
  let cap-dy = if at-top { w / 2 } else { -w }
  let corner(sx) = {
    let p(x, y) = (sx * (x - w / 2), sy * y) // The middle of the side
    place(top + left, curve(fill: white,
      curve.move(p(-s, -s)), curve.line(p(r, -s)), curve.line(p(r, 0pt)),
      curve.cubic(p(r - k * r, 0pt), p(0pt, r - k * r), p(0pt, r)),
      curve.line(p(-s, r)), curve.close()))
    place(top + left, curve(stroke: frame-stroke,
      curve.move(p(r, 0pt)), curve.cubic(p(r - k * r, 0pt), p(0pt, r - k * r), p(0pt, r))))
  }
  place(y + left, box(width: 100%, height: 0pt, {
    if separator-x != none {
      place(top + left, dy: cap-dy, rect(width: separator-x, height: w / 2, fill: gutter-fill, stroke: none))
      place(top + left, dx: separator-x, dy: cap-dy, rect(width: 100% - separator-x, height: w / 2, fill: code-paint, stroke: none))
    }
    place(top + left, corner(1))
    place(top + right, box(width: 0pt, corner(-1)))
    place(top + left, dx: r - w / 2, line(length: 100% - 2 * r + w, stroke: frame-stroke))
  }))
}
// The sides are the gray fill around the white block with the code. The corners are drawn twice: here over the
// sides and in the header and the footer of codly over the lines, codly cuts them at its border
// Line numbers have a fixed width, so the line after them is the left side of a block around the code: codly
// paints the fills over the strokes of cells, a block draws its stroke over the content
#let code-frame(it) = block(breakable: true, width: 100%, inset: (x: frame-stroke.thickness),
  fill: frame-stroke.paint, {
    code-cap(true)
    block(breakable: true, width: 100%, fill: white, context {
      let inset = (left: 1.5pt, right: 1.2pt, y: 1.07pt)
      let width = measure("0" * str(it.lines.len()).len()).width + inset.left + inset.right
      let last-index = calc.rem(it.lines.len(), 2)
      // The line after the numbers is the right edge of the fill: codly paints the fills over the strokes of cells
      let sep = (1 - code-stroke.thickness / width) * 100%
      let edge(c) = gradient.linear((c, 0%), (c, sep), (code-stroke.paint, sep), (code-stroke.paint, 100%))
      let gutter-fills = (white, code-fill).map(edge)
      let row-fills = (code-fill, white)
      show: codly.set_(gutters: (codly.gutter-column(
        values: row => if row.kind == "code" { bold-l(str(row.number), size: code-size) },
        fill: gutter-fills, // Inverse of the line
        align: right + horizon, // Digits stay under each other: 9 and 10
        width: width, inset: inset
      ),),
        header: place(top + right, [#metadata(none)<code-corner>]) + code-cap(true, separator-x: width, gutter-fill: gutter-fills.at(1), code-paint: row-fills.at(1)),
        footer: code-cap(false, y: bottom, separator-x: width,
          gutter-fill: gutter-fills.at(last-index), code-paint: row-fills.at(last-index)),
      )
      codly.new(it)
    })
    code-cap(false, y: bottom)
  })

// Line break that leaves the real newline outside, so the next line can start with "="
#let br = raw("\n")


// Inline code: does not change the line height
#let code-file(path) = raw(read("/" + path).replace("\r\n", "\n").trim(at: end).split("\n")
  .map(l => if comment-of(l) == none { l } else { l + " " }).join("\n"), lang: path.split(".").last(), block: true)

#let code(str) = box(
  radius: 3pt,
  inset: (x: 2pt),
  outset: (y: 1.8pt),
  fill: code-fill,
  {
    show "—": "-" // undo the dash rule of the text
    text(font: "Courier New", size: font-sizes.code, bold-l(str))
  }
)

// Long table cut into `parts` tables standing in a row, each one repeats the header
#let split-table(parts, header, ..cells) = {
  let rows = cells.pos().chunks(header.len())
  align(center, grid(
    columns: parts,
    column-gutter: 1.5pt,
    ..rows.chunks(calc.ceil(rows.len() / parts)).map(part => table(
      columns: header.len(),
      ..header.map(strong),
      ..part.flatten()
    ))
  ))
}

// First piece of text inside content
#let first-str(it) = {
  if type(it) == str { it }
  else if it.func() == text { it.text }
  else if it.has("children") { it.children.map(first-str).find(x => x != "") }
  else if it.has("body") { first-str(it.body) }
  else { "" }
}
// Page number as it is drawn in the corners
#let page-num(body) = text(font: "Times New Roman", size: 11pt, top-edge: "cap-height", bottom-edge: "baseline", body)

// Text of a heading without its styles and line breaks, formulas stay
#let plain(it) = {
  if type(it) == str { it }
  else if it.func() == text { it.text }
  else if it.func() == raw { it.text.trim() }
  else if it.func() == math.equation { it }
  else if it.has("children") { it.children.map(plain).join() }
  else if it.has("body") { plain(it.body) }
  else if it.func() == [ ].func() { " " }
}
// Table of contents: headings of levels 1 and 2 in two columns, page and column (a, b, c) of each
#let toc() = context {
  let width = page.width - 2 * margin.x
  let col-width = (width - (cols-cnt - 1) * gutter) / cols-cnt
  let entry(el) = {
    let pos = el.location().position()
    let col = calc.min(cols-cnt - 1, calc.max(0, calc.floor((pos.x - margin.x + 1pt) / (col-width + gutter))))
    let where = str(counter(page).at(el.location()).first()) + "abcdefgh".at(col)
    let body = if el.level == 1 { text(weight: "bold", plain(el.body)) } else { h(4pt) + plain(el.body) }
    // Wrapped lines start under the text of the heading, not under its number
    let num = first-str(el.body).match(regex("^[0-9.]+ "))
    let indent = if num == none { 8pt } else {
      measure(if el.level == 1 { text(weight: "bold", num.text) } else { h(4pt) + num.text }).width
    }
    par(hanging-indent: indent, link(el.location(), body + " " + box(width: 1fr, text(fill: rgb("#999999"), repeat(gap: 1.5pt)[.])) + sym.wj + box(h(2pt) + where)))
  }
  let num = measure(page-num(counter(page).display())).width + 2pt
  let all = query(heading.where(level: 1).or(heading.where(level: 2))).map(entry)
  let half = calc.ceil(all.len() / 2)
  block(above: 0pt, below: 4pt, {
    set text(size: 6.5pt)
    set par(leading: 1.9pt, spacing: 1.9pt, hanging-indent: 8pt)
    h(num) + text(size: font-sizes.h3, weight: "bold")[Оглавление]
    h(1fr) + text(fill: rgb("#4d4d4d"))[a, b, c - номера столбцов]
    v(1.5pt)
    grid(columns: (1fr, 1fr), column-gutter: 6pt,
      all.slice(0, half).join(), all.slice(half).join())
    v(2pt)
    line(length: 100%, stroke: 0.5pt + rgb("#888888"))
  })
}
#let setup(body) = {
  set page(
    paper: "a4",
    flipped: true, // Альбомная ориентация
    margin: margin, // Узкие поля для экономии места
    columns: cols-cnt,
  
    background: align(top,
      layout(size => {
        // Вычисляем полезную ширину текста
        let width = size.width - 2 * margin.x
        // Ширина одной колонки
        let col-width = (width - (cols-cnt - 1) * gutter) / cols-cnt
      
        // Настройки линии: серая, пунктирная (dashed) или точечная (dotted)
        let line-style = (paint: rgb("#888888"), thickness: 0.5pt, dash: (15pt, 7pt))
      
        // Координаты Y (от верхнего поля до нижнего)
        let y-start = 0pt
        let y-end = size.height
      
        // Рисуем первую линию
        let x1 = margin.x + col-width + gutter / 2
        place(top + left, line(start: (x1, y-start), end: (x1, y-end), stroke: line-style))
        // Рисуем вторую линию
        let x2 = x1 + col-width + gutter
        place(top + left, line(start: (x2, y-start), end: (x2, y-end), stroke: line-style))
      }),
    ),

  
    // Page number in all 4 corners, so it is seen when most of the page is covered.
    // It overlaps the text a bit, so it has a white outline.
    foreground: context {
      let num = page-num(counter(page).display())
      for corner in (top + left, top + right, bottom + left, bottom + right) {
        place(
          corner,
          dx: if corner.x == left { margin.x } else { -margin.x },
          dy: if corner.y == top { margin.y } else { -margin.y },
          {
            place(text(fill: black.transparentize(30%), stroke: 3pt + white.transparentize(30%), num))
            num
          }
        )
      }
    }
  )
  set columns(gutter: gutter) // Устанавливаем gutter между колонками
  set text(
    // Digits are from Gelasio (fonts/): in Georgia they have different heights
    font: ((name: "Gelasio", covers: regex("[0-9]")), "Georgia"), number-type: "lining", slashed-zero: true,
    size: font-sizes.text
  )
  set par(leading: 2.5pt)
  // A hyphen that is a separate word is a dash
  show regex("(^|\\s)-(\\s|$)"): m => m.text.replace("-", "—")
  // Level 3: the gap above is the same as under it
  show heading: it => block(above: if it.depth == 3 { 4pt } else { 2.5pt }, sticky: true, context {
    // At the top of the first column the page number covers the start of the heading: shift it
    let p = here().position()
    if p.x < margin.x + 1pt and (p.y < margin.y + 5pt or p.y > page.height - margin.y - 12pt) {
      h(measure(page-num(counter(page).display())).width + 2pt)
    }
    // The number at the start: smaller thin italic, a bit lighter than black. The font is in fonts/
    show regex("^\\d+(\\.\\d+)*\\."): n => strong(delta: -300, text(font: "Old Standard TT", style: "italic",
      size: font-sizes.at("num" + str(it.depth)), slashed-zero: false, fill: rgb("#4d4d4d"), n))
    text(size: font-sizes.at("h" + str(it.depth)), weight: "regular", it.body)
  })
  // Math
  show math.equation.where(block: true): set text(size: font-sizes.math-block)
  show math.equation.where(block: false): set text(size: math-inline-scale * 1em)
  // Inline fractions in a line: a/b
  show math.equation.where(block: false): set math.frac(style: "horizontal")
  // Block formulas: wider space after a comma between formulas, but not inside brackets and indices: f(i, j), c_(i, j)
  show math.equation.where(block: true): it => {
    let gap = h(10pt)
    show ",": math.class("punctuation", ",") + gap
    show math.lr: it => { show h.where(amount: 10pt): none; it }
    show math.attach: it => { show h.where(amount: 10pt): none; it }
    it
  }
  // The same gap above and under a formula, between two formulas it is smaller.
  // A multi-level formula (fractions, matrices) looks farther from the text above it, so a part of the gap goes under it
  show math.equation.where(block: true): it => context {
    let tall = measure(it).height > 14pt
    set block(above: if tall { 2.25pt } else { 3.25pt }, below: if tall { -4.75pt } else { -5.25pt })
    it
  }
  set table(inset: 3pt, stroke: 0.5pt)
  show table: set block(
    above: 8pt,
    below: -5pt
  )

  // Code
  show raw.where(block: true): code-frame
  show: codly.set_(
    radius: 0pt, // The border is drawn by code-frame
    leading: 0.07em,
    number-enabled: false, // Line numbers are a gutter column of code-frame
    header: code-cap(true), // Not repeated on breaks
    footer: code-cap(false),
    lang-position: none, // Drawn by the lines
    indent-guides: (width: 4, color: luma(40%).transparentize(40%), thickness: 0.3pt)
  )
  show: codly.header-set_(repeat: false, inset: (x: 0pt, y: 0pt, bottom: 1pt), fill: none, stroke: none)
  show: codly.footer-set_(repeat: false, inset: (x: 0pt, y: 0pt, top: 1pt), fill: none, stroke: none)
  show: codly.line-set_(fill: (code-fill, white), stroke: none, inset: (left: 0.3pt, right: -1pt, y: 1.07pt))
  set raw(theme: "/BW.tmTheme", tab-size: 4)
  // Not show text: it would override the font of the dotted 0 in bold-l
  show raw.where(block: true): set text(font: "Courier New", size: code-size)
  show raw: it => {
    show "—": "-" // Not in code
    if it.text.trim() == "" { // Repeated spaces and enters: the font and the size of the text around
      return it.text.split("\n").join(linebreak())
    }
    // Code
    set par(leading: 0.35em)
    set block(spacing: 5pt, below: -2.5pt) // below + height of the text line after the code = gap under the code
    if it.lang == none { // Styled text
      show text: set text(font: "Courier New")
      block(it.text)
      return
    }
    show text.where(fill: rgb("#505050")): set text(font: "Caveat", size: 9.5pt) // Comments, the font is in fonts/
    // codly renders lines outside of the rules of the raw, so the fixes go on each line
    // The label of the language hangs from the top right corner of the block (mark in code-cap). codly draws its
    // label before the lines, under the comments, so the last line that can touch it draws it instead:
    // line 2 if it is in the column of the corner, else line 1
    show raw.line: l => {
      if l.number <= 2 {
        let mark = if l.number == 1 { <code-line-1> } else { <code-line-2> }
        let badge = box(fill: white.transparentize(30%), stroke: code-stroke, inset: (x: 1.5pt, y: 1.2pt), radius: 1.5pt,
          text(font: "Courier New", size: code-size, fill: black, weight: "regular", it.lang))
        // Empty box: on the baseline, not a part of the line
        box(context {
          let at = here().position()
          let pos(marks, i) = if marks.len() > 0 { marks.at(i).location().position() }
          let corner = pos(query(selector(<code-corner>).before(here())), -1)
          if corner == none { return } // Measured by codly
          let same(p) = p.page == corner.page and p.x < corner.x and p.y >= corner.y
          let second = if l.count > 1 { pos(query(selector(<code-line-2>).after(here(), inclusive: true)), 0) }
          if (l.number == 2) != (second != none and same(second)) { return }
          place(top + left, dx: corner.x - at.x - measure(badge).width + badge-shift.x, dy: corner.y - at.y + badge-shift.y, badge)
        } + [#metadata(none)#mark])
      }
      bold-l(l, size: code-size)
    }
    it
  }

  counter(page).update(0)
  body
}
