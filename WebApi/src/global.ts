export function ajustNumber(params: string) {
  let itm = parseFloat(params.split(".").join("").split(",").join("."));

  if (isNaN(itm)) {
    return 0;
  }
  return itm;
}

export function ajustDate(params: string): Date {
  if (params === "00/00/0000") {
    return null;
  }

  let dt_1 = params.split("/");
  let dt: any;

  if (dt_1[2].length == 2) {
    dt = new Date(
      parseInt("20" + dt_1[2]),
      parseInt(dt_1[1]) - 1,
      parseInt(dt_1[0])
    );
  } else if (dt_1[2].length == 4) {
    dt = new Date(parseInt(dt_1[2]), parseInt(dt_1[1]) - 1, parseInt(dt_1[0]));
  }

  if (!dt) return null;

  return dt;
}
